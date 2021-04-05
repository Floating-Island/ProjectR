// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/DeloreanReplicationMachine.h"
#include "Jet/SteerStates/CenterSteerState.h"
#include "Jet/SteerStates/SteerState.h"
#include "Jet/MotorStates/MotorState.h"
#include "extensions/PxRigidBodyExt.h"
#include "PhysXPublic.h"
#include "Jet/Jet.h"
#include "Track/TrackManager.h"
#include "Kismet/GameplayStatics.h"

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

void UDeloreanReplicationMachine::smooth(int atPosition, const FMovementData& aTargetMovement)
{
	int64 timePhaseShift = FMath::Abs(movementHistory[0].timestampedStates.timestamp - aTargetMovement.timestampedStates.timestamp);
	float interpolationStep = timePhaseShift / 1000.0f;

	FVector smoothedLocation = FMath::CubicInterp(movementHistory[atPosition].location, movementHistory[atPosition].linearVelocity, aTargetMovement.location, aTargetMovement.linearVelocity, interpolationStep);
	FVector smoothedLinearVelocity = FMath::CubicInterpDerivative(movementHistory[atPosition].location, movementHistory[atPosition].linearVelocity, aTargetMovement.location, aTargetMovement.linearVelocity, interpolationStep);

	movementHistory[atPosition].location = smoothedLocation;
	movementHistory[atPosition].linearVelocity = smoothedLinearVelocity;
	
	movementHistory[atPosition].angularVelocityInRadians = FMath::LerpStable(movementHistory[atPosition].angularVelocityInRadians, aTargetMovement.angularVelocityInRadians, interpolationStep);
	
	movementHistory[atPosition].rotation = (FQuat::Slerp(movementHistory[atPosition].rotation.Quaternion(), aTargetMovement.rotation.Quaternion(), interpolationStep)).Rotator();
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
			movementHistory[0].timestampedStates.motorStateClass = aBunchOfStates.motorStateClass;
			movementHistory[0].timestampedStates.steerStateClass = aBunchOfStates.steerStateClass;
			movementHistory[0].type = EMovementType::sendOrReceive;
			owningJet->asCurrentMovementSet(movementHistory[0], this);
			establishMovementForTheClientFrom(0, aBunchOfStates.timestamp);//save moment to send to the client...
		}
		else
		{
			if(historyMoment > 0)
			{
				movementHistory[historyMoment].timestampedStates.motorStateClass = aBunchOfStates.motorStateClass;
				movementHistory[historyMoment].timestampedStates.steerStateClass = aBunchOfStates.steerStateClass;
				movementHistory[historyMoment].type = EMovementType::sendOrReceive;
				reshapeHistoryFrom(historyMoment, true);//chain reaction of history rewrite
				establishMovementForTheClientFrom(historyMoment, aBunchOfStates.timestamp);//save moment to send to the client...
			}
		}
	}
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
		if(needsToChangeStates && nextMovementInHistory.type == EMovementType::routine)
		{
			nextMovementInHistory.timestampedStates.motorStateClass = currentMovementInHistory.timestampedStates.motorStateClass;
			nextMovementInHistory.timestampedStates.steerStateClass = currentMovementInHistory.timestampedStates.steerStateClass;
		}
		else //found the first movement in history that was already sent to or received from the server...
		{
			needsToChangeStates = false;
		}
		FStateData nextMovementStates = nextMovementInHistory.timestampedStates;

		FMovementData rewrittenNextMovement = FMovementData();

		rewrittenNextMovement = simulateNextMovementFrom(currentMovementInHistory);//calculate rewritten next movement with these values... 
		
		nextMovementInHistory.regenerateMoveFrom(rewrittenNextMovement, nextMovementInHistory.type);
		nextMovementInHistory.timestampedStates = nextMovementStates;
		
		if(needsToAlign)
		{
			needsToAlign = false;
			float timeBetweenMovements = (nextMovementInHistory.timestampedStates.timestamp - currentMovementInHistory.timestampedStates.timestamp) / 1000.0f;
			nextMovementInHistory.linearVelocity += (steerCounterAcceleration + steerAlignAcceleration) * timeBetweenMovements;
			nextMovementInHistory.location = currentMovementInHistory.location + nextMovementInHistory.linearVelocity * timeBetweenMovements;
		}
		
		if(currentMovementInHistory.timestampedStates.steerStateClass != UCenterSteerState::StaticClass())
		{
			needsToAlign = true;
			owningJet->asCurrentMovementSet(currentMovementInHistory, this);
			FVector currentForwardProjection = owningJet->ForwardProjectionOnFloor();
			FVector currentLocation = owningJet->GetActorLocation();
			owningJet->asCurrentMovementSet(nextMovementInHistory, this);
			float alignmentAcceleration =  owningJet->accelerationMagnitudeToAlignVelocityFrom(currentLocation);
			steerCounterAcceleration = (-currentForwardProjection) * alignmentAcceleration;
			steerAlignAcceleration = owningJet->ForwardProjectionOnFloor() * alignmentAcceleration;
		}
		--aMomentInHistory;
	}
	owningJet->asCurrentMovementSet(movementHistory[0], this);
}

FMovementData UDeloreanReplicationMachine::simulateNextMovementFrom(FMovementData aPreviousMovement, float simulationDuration)
{
	owningJet->asCurrentMovementSet(aPreviousMovement, this);

	FVector auxiliaryLinearAcceleration = FVector(0);
	FVector auxiliaryAngularAcceleration = FVector(0);
	owningJet->changesGeneratedByAntiGravityTo(auxiliaryLinearAcceleration, auxiliaryAngularAcceleration);

	FVector sumOfLinearAccelerations = FVector(0);
	sumOfLinearAccelerations += auxiliaryLinearAcceleration;
	
	FVector sumOfAngularAccelerations = FVector(0);
	sumOfAngularAccelerations += auxiliaryAngularAcceleration;

	auxiliaryLinearAcceleration = FVector(0);
	auxiliaryAngularAcceleration = FVector(0);
	Cast<USteerState, UObject>(aPreviousMovement.timestampedStates.steerStateClass->ClassDefaultObject)->changesMadeTo(owningJet, auxiliaryLinearAcceleration, auxiliaryAngularAcceleration);
	
	sumOfAngularAccelerations += auxiliaryAngularAcceleration;
	sumOfLinearAccelerations += auxiliaryLinearAcceleration;

	sumOfLinearAccelerations += Cast<UMotorState, UObject>(aPreviousMovement.timestampedStates.motorStateClass->ClassDefaultObject)->linearAccelerationsGeneratedTo(owningJet);
	sumOfLinearAccelerations += retrieveTrackMagnetizationLinearAcceleration();

	if(simulationDuration == 0)
	{
		simulationDuration = GetWorld()->GetDeltaSeconds();
	}

	float effectiveLinearDampingEffect = 1 - owningJet->linearDamping() * simulationDuration;
	float effectiveAngularDampingEffect = 1 - owningJet->angularDamping() * simulationDuration;
	
	sumOfLinearAccelerations *=  effectiveLinearDampingEffect;
	sumOfAngularAccelerations *= effectiveAngularDampingEffect;

	FVector netForceApplied = sumOfLinearAccelerations * owningJet->mass();
	FVector netTorqueApplied = sumOfAngularAccelerations * owningJet->mass();

	PxVec3 linearVelocityDelta = PxVec3();
	PxVec3 angularVelocityDelta = PxVec3();

	PxRigidBody* body = FPhysicsInterface_PhysX::GetPxRigidBody_AssumesLocked(owningJet->physicsHandleRequestedBy(this));

	PxRigidBodyExt::computeVelocityDeltaFromImpulse(*body, 
		U2PVector(netForceApplied) * simulationDuration, 
		U2PVector(netTorqueApplied) * simulationDuration, 
		linearVelocityDelta, 
		angularVelocityDelta
	);

	FMovementData simulatedMove = aPreviousMovement;

	simulatedMove.linearVelocity += P2UVector(linearVelocityDelta);
	
	simulatedMove.location += simulatedMove.linearVelocity * simulationDuration;
	
	simulatedMove.angularVelocityInRadians += FVector::DegreesToRadians(P2UVector(angularVelocityDelta));

	FVector angularRotation = simulatedMove.angularVelocityInRadians * simulationDuration;
	
	FQuat angularVelocityQuaternion = FQuat(angularRotation.GetSafeNormal(), angularRotation.Size());

	simulatedMove.rotation =  ( angularVelocityQuaternion * simulatedMove.rotation.Quaternion() ).Rotator();
	
	return simulatedMove;
}

FVector UDeloreanReplicationMachine::retrieveTrackMagnetizationLinearAcceleration()
{
	ATrackManager* trackManager = Cast<ATrackManager, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ATrackManager::StaticClass()));
	if(trackManager == nullptr)
	{
		return FVector(0, 0, - FMath::Abs(GetWorld()->GetGravityZ()));
	}
	return trackManager->pullingAccelerationTo(owningJet);
}