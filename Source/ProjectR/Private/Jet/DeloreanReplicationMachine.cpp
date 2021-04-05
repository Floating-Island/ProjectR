// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/DeloreanReplicationMachine.h"
#include "Jet/SteerStates/CenterSteerState.h"
#include "Jet/SteerStates/SteerState.h"
#include "Jet/MotorStates/MotorState.h"
#include "extensions/PxRigidBodyExt.h"
#include "PhysXPublic.h"
#include "Jet/Jet.h"

UDeloreanReplicationMachine::UDeloreanReplicationMachine()
{
	generateSendOrReceiveMovementType = false;
	owningJet = nullptr;
	synchronizedMovement = FMovementData();
	readyToEstablishMovement = false;
}

void UDeloreanReplicationMachine::setDefaultVariablesTo(AJet* anOwner, int aMovementHistorySize)
{
	owningJet = anOwner;
	movementHistorySize = aMovementHistorySize;
	movementHistory = std::deque<FMovementData>(movementHistorySize, 
		FMovementData(owningJet, EMovementType::routine, owningJet->currentMotorStateClass(), owningJet->currentSteerStateClass()));
}

bool UDeloreanReplicationMachine::hasDataForClient()
{
	return readyToEstablishMovement;
}

void UDeloreanReplicationMachine::addMovementToHistory()
{
	addToMovementHistory(FMovementData(owningJet, 
		generateSendOrReceiveMovementType? EMovementType::sendOrReceive : EMovementType::routine, 
		owningJet->currentMotorStateClass(), 
		owningJet->currentSteerStateClass()));
	generateSendOrReceiveMovementType = false;
}

void UDeloreanReplicationMachine::addToMovementHistory(FMovementData aMovement)
{
	movementHistory.push_front(aMovement);
	movementHistory.pop_back();
}

FStateData UDeloreanReplicationMachine::generateCurrentStateDataToSend()
{
	FStateData currentStates = FStateData(owningJet->currentMotorStateClass(), owningJet->currentSteerStateClass());

	generateSendOrReceiveMovementType = true;
	
	return currentStates;
}

FMovementData UDeloreanReplicationMachine::retrieveCurrentMovementDataToSend()
{
	return synchronizedMovement;
}

void UDeloreanReplicationMachine::synchronizeMovementHistoryWith(FStateData aBunchOfStates)
{	
	readyToEstablishMovement = false;
	int historyMoment = closestIndexTo(aBunchOfStates.timestamp);
	if(historyMoment != movementHistory.size())
	{
		if(historyMoment <= 0)
		{
			changeHistoryMovementAtMomentWith(aBunchOfStates, 0);
			owningJet->asCurrentMovementSet(movementHistory[0], this);
			establishMovementForTheClientFrom(0, aBunchOfStates.timestamp);//save moment to send to the client...
		}
		else
		{
			if(historyMoment > 0)
			{
				changeHistoryMovementAtMomentWith(aBunchOfStates, historyMoment);
				reshapeHistoryFrom(historyMoment, true);//chain reaction of history rewrite
				establishMovementForTheClientFrom(historyMoment, aBunchOfStates.timestamp);//save moment to send to the client...
			}
		}
	}
}

int UDeloreanReplicationMachine::closestIndexTo(int64 aTimestamp)
{
	int historyMoment = 0;
	int minimumDifference = std::numeric_limits<int>::max();
	if(aTimestamp < movementHistory[0].timestampedStates.timestamp)//check that the timestamp doesn't come from the future...
	{
		while (historyMoment < movementHistory.size())
		{
			const int currentDifference = FMath::Abs(movementHistory[historyMoment].timestampedStates.timestamp - aTimestamp);

			if( currentDifference < minimumDifference)
			{
				minimumDifference = currentDifference;
			}
			else
			{
				break;
			}
			++historyMoment;
		}
	}
	return --historyMoment;
}

void UDeloreanReplicationMachine::changeHistoryMovementAtMomentWith(FStateData aBunchOfStates, int atHistoryMoment)
{
	movementHistory[atHistoryMoment].timestampedStates.motorStateClass = aBunchOfStates.motorStateClass;
	movementHistory[atHistoryMoment].timestampedStates.steerStateClass = aBunchOfStates.steerStateClass;
	movementHistory[atHistoryMoment].type = EMovementType::sendOrReceive;
}

void UDeloreanReplicationMachine::synchronizeMovementHistoryWith(FMovementData aMovementStructure)
{	
	readyToEstablishMovement = false;
	FMovementData initialCurrentMovement = movementHistory[0];
	
	int historyMoment = closestIndexTo(aMovementStructure.timestampedStates.timestamp);
	if(historyMoment != movementHistory.size() && historyMoment >=0)
	{
		movementHistory[historyMoment].copyMovesFrom(aMovementStructure); /*smooth(historyMoment, aMovementStructure);*/ 
		reshapeHistoryFrom(historyMoment, false);//chain reaction of history rewrite

		smoothFinalMovementFrom(initialCurrentMovement, aMovementStructure.timestampedStates.timestamp);
	}
}

void UDeloreanReplicationMachine::reshapeHistoryFrom(int aMomentInHistory, bool anOptionToChangeStates)
{
	bool needsToChangeStates = anOptionToChangeStates;

	FVector steerCounterAcceleration = FVector(0);
	FVector steerAlignAcceleration = FVector(0);
	bool needsToAlign = false;
	while(aMomentInHistory > 0)
	{
		FMovementData& currentMovementInHistory = movementHistory[aMomentInHistory];
		FMovementData& nextMovementInHistory = movementHistory[aMomentInHistory - 1];

		copyCurrentMovementStatesToNextIf(needsToChangeStates, currentMovementInHistory, nextMovementInHistory);

		FStateData nextMovementStates = nextMovementInHistory.timestampedStates;

		FMovementData rewrittenNextMovement = FMovementData();

		rewrittenNextMovement = simulateNextMovementFrom(currentMovementInHistory);//calculate rewritten next movement with these values... 
		
		nextMovementInHistory.regenerateMoveFrom(rewrittenNextMovement, nextMovementInHistory.type);
		nextMovementInHistory.timestampedStates = nextMovementStates;
		
		manageVelocityAlignmentWhen(needsToAlign, steerCounterAcceleration, steerAlignAcceleration, currentMovementInHistory,
		                             nextMovementInHistory);
		--aMomentInHistory;
	}
	owningJet->asCurrentMovementSet(movementHistory[0], this);
}

void UDeloreanReplicationMachine::copyCurrentMovementStatesToNextIf(bool& needsToChangeStates, FMovementData& aCurrentMovementInHistory, FMovementData& aNextMovementInHistory)
{
	if(needsToChangeStates && aNextMovementInHistory.type == EMovementType::routine)
	{
		aNextMovementInHistory.timestampedStates.motorStateClass = aCurrentMovementInHistory.timestampedStates.motorStateClass;
		aNextMovementInHistory.timestampedStates.steerStateClass = aCurrentMovementInHistory.timestampedStates.steerStateClass;
	}
	else //found the first movement in history that was already sent to or received from the server...
	{
		needsToChangeStates = false;
	}
}

FMovementData UDeloreanReplicationMachine::simulateNextMovementFrom(const FMovementData& aPreviousMovement, float simulationDuration)
{
	owningJet->asCurrentMovementSet(aPreviousMovement, this);

	FVector sumOfLinearAccelerations;
	FVector sumOfAngularAccelerations;
	
	calculateNextMovementChangesTo(sumOfLinearAccelerations, sumOfAngularAccelerations, simulationDuration, aPreviousMovement);

	PxVec3 linearVelocityDelta = PxVec3();
	PxVec3 angularVelocityDelta = PxVec3();

	calculatePhysicsBodyChangesTo(linearVelocityDelta, angularVelocityDelta, simulationDuration, sumOfLinearAccelerations,
	                              sumOfAngularAccelerations);
	
	return generateSimulatedMoveFrom(aPreviousMovement, P2UVector(linearVelocityDelta), P2UVector(angularVelocityDelta), simulationDuration);; 
}

void UDeloreanReplicationMachine::calculateNextMovementChangesTo(FVector& aSumOfLinearAccelerations, FVector& aSumOfAngularAccelerations, float& aSimulationDuration, const
                                                                 FMovementData& aPreviousMovement)
{
	FVector auxiliaryLinearAcceleration = FVector(0);
	FVector auxiliaryAngularAcceleration = FVector(0);
	owningJet->changesGeneratedByAntiGravityTo(auxiliaryLinearAcceleration, auxiliaryAngularAcceleration);

	aSumOfLinearAccelerations = FVector(0);
	aSumOfLinearAccelerations += auxiliaryLinearAcceleration;

	aSumOfAngularAccelerations = FVector(0);
	aSumOfAngularAccelerations += auxiliaryAngularAcceleration;

	auxiliaryLinearAcceleration = FVector(0);
	auxiliaryAngularAcceleration = FVector(0);
	Cast<USteerState, UObject>(aPreviousMovement.timestampedStates.steerStateClass->ClassDefaultObject)->changesMadeTo(owningJet, auxiliaryLinearAcceleration, auxiliaryAngularAcceleration);
	
	aSumOfAngularAccelerations += auxiliaryAngularAcceleration;
	aSumOfLinearAccelerations += auxiliaryLinearAcceleration;

	aSumOfLinearAccelerations += Cast<UMotorState, UObject>(aPreviousMovement.timestampedStates.motorStateClass->ClassDefaultObject)->linearAccelerationsGeneratedTo(owningJet);
	aSumOfLinearAccelerations += owningJet->retrieveTrackMagnetizationLinearAcceleration();

	if(aSimulationDuration == 0)
	{
		aSimulationDuration = GetWorld()->GetDeltaSeconds();
	}

	float effectiveLinearDampingEffect = 1 - owningJet->linearDamping() * aSimulationDuration;
	float effectiveAngularDampingEffect = 1 - owningJet->angularDamping() * aSimulationDuration;
	
	aSumOfLinearAccelerations *=  effectiveLinearDampingEffect;
	aSumOfAngularAccelerations *= effectiveAngularDampingEffect;
}

void UDeloreanReplicationMachine::calculatePhysicsBodyChangesTo(PxVec3& aLinearVelocityDelta, PxVec3& anANgularVelocityDelta, const float& simulationDuration, const FVector&
                                                                aSumOfLinearAccelerations, const FVector& aSumOfAngularAccelerations)
{
	FVector netForceApplied = aSumOfLinearAccelerations * owningJet->mass();
	FVector netTorqueApplied = aSumOfAngularAccelerations * owningJet->mass();

	PxRigidBody* body = FPhysicsInterface_PhysX::GetPxRigidBody_AssumesLocked(owningJet->physicsHandleRequestedBy(this));

	PxRigidBodyExt::computeVelocityDeltaFromImpulse(*body, 
	                                                U2PVector(netForceApplied) * simulationDuration, 
	                                                U2PVector(netTorqueApplied) * simulationDuration, 
	                                                aLinearVelocityDelta, 
	                                                anANgularVelocityDelta
	);
}

FMovementData UDeloreanReplicationMachine::generateSimulatedMoveFrom(const FMovementData& aPreviousMovement,
                                                                     FVector aLinearVelocityDelta, FVector anAngularVelocityDelta, float aSimulationDuration)
{
	FMovementData simulatedMove = aPreviousMovement;

	simulatedMove.linearVelocity += aLinearVelocityDelta;
	
	simulatedMove.location += simulatedMove.linearVelocity * aSimulationDuration;
	
	simulatedMove.angularVelocityInRadians += FVector::DegreesToRadians(anAngularVelocityDelta);

	FVector angularRotation = simulatedMove.angularVelocityInRadians * aSimulationDuration;
	
	FQuat angularVelocityQuaternion = FQuat(angularRotation.GetSafeNormal(), angularRotation.Size());

	simulatedMove.rotation =  ( angularVelocityQuaternion * simulatedMove.rotation.Quaternion() ).Rotator();

	return simulatedMove;
}

void UDeloreanReplicationMachine::manageVelocityAlignmentWhen(bool& needsToAlign, FVector& aSteerCounterAcceleration, FVector& aSteerAlignAcceleration,
	FMovementData& aCurrentMovementInHistory, FMovementData& aNextMovementInHistory)
{
	if(needsToAlign)
	{
		needsToAlign = false;
		float timeBetweenMovements = (aNextMovementInHistory.timestampedStates.timestamp - aCurrentMovementInHistory.timestampedStates.timestamp) / 1000.0f;
		aNextMovementInHistory.linearVelocity += (aSteerCounterAcceleration + aSteerAlignAcceleration) * timeBetweenMovements;
		aNextMovementInHistory.location = aCurrentMovementInHistory.location + aNextMovementInHistory.linearVelocity * timeBetweenMovements;
	}
		
	if(aCurrentMovementInHistory.timestampedStates.steerStateClass != UCenterSteerState::StaticClass())
	{
		needsToAlign = true;
		owningJet->asCurrentMovementSet(aCurrentMovementInHistory, this);
		FVector currentForwardProjection = owningJet->ForwardProjectionOnFloor();
		FVector currentLocation = owningJet->GetActorLocation();
		owningJet->asCurrentMovementSet(aNextMovementInHistory, this);
		float alignmentAcceleration =  owningJet->accelerationMagnitudeToAlignVelocityFrom(currentLocation);
		aSteerCounterAcceleration = (-currentForwardProjection) * alignmentAcceleration;
		aSteerAlignAcceleration = owningJet->ForwardProjectionOnFloor() * alignmentAcceleration;
	}
}

void UDeloreanReplicationMachine::establishMovementForTheClientFrom(int aMomentInHistory, int64 aClientTimestamp)
{
	synchronizedMovement = movementHistory[aMomentInHistory];
	synchronizedMovement.timestampedStates.timestamp = aClientTimestamp;
	readyToEstablishMovement = true;
}

void UDeloreanReplicationMachine::smoothFinalMovementFrom(FMovementData initialMovement, int64 aTimestamp)
{
	int64 timePhaseShift = FMath::Abs(movementHistory[0].timestampedStates.timestamp - aTimestamp);
	float interpolationStep = timePhaseShift / 1000.0f;

	FVector smoothedLocation = FMath::LerpStable(initialMovement.location, movementHistory[0].location, interpolationStep);
	//FMath::CubicInterp(initialMovement.location, initialMovement.linearVelocity, movementHistory[0].location, movementHistory[0].linearVelocity, interpolationStep);
	FVector smoothedLinearVelocity = FMath::LerpStable(initialMovement.linearVelocity, movementHistory[0].linearVelocity, interpolationStep);
	//FMath::CubicInterpDerivative(initialMovement.location, initialMovement.linearVelocity, movementHistory[0].location, movementHistory[0].linearVelocity, interpolationStep);

	movementHistory[0].location = smoothedLocation;
	movementHistory[0].linearVelocity = smoothedLinearVelocity;

	movementHistory[0].angularVelocityInRadians = FMath::LerpStable(initialMovement.angularVelocityInRadians, movementHistory[0].angularVelocityInRadians, interpolationStep);
	
	movementHistory[0].rotation = (FQuat::Slerp(initialMovement.rotation.Quaternion(), movementHistory[0].rotation.Quaternion(), interpolationStep)).Rotator();
	//FMath::RInterpTo(initialMovement.rotation, movementHistory[0].rotation, interpolationStep, movementHistory[0].angularVelocityInRadians.Size());
	owningJet->asCurrentMovementSet(movementHistory[0], this);
}