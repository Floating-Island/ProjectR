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
}

void UDeloreanReplicationMachine::setDefaultVariablesTo(AJet* anOwner, int aMovementHistorySize)
{
	owningJet = anOwner;
	movementHistorySize = aMovementHistorySize;
	movementHistory = std::deque<FMovementData>(movementHistorySize, 
		FMovementData(owningJet, EMovementType::routine, owningJet->currentMotorStateClass(), owningJet->currentSteerStateClass()));
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

			UE_LOG(LogTemp, Log, TEXT("current movement history number: %s"), *FString::FromInt(historyMoment));
			UE_LOG(LogTemp, Log, TEXT("minimum difference: %s"), *FString::FromInt(minimumDifference));
			UE_LOG(LogTemp, Log, TEXT("current difference: %s"), *FString::FromInt(currentDifference));

			if( currentDifference < minimumDifference)
			{
				minimumDifference = currentDifference;
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("found closest index to received timestamp."));
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
	//never change timestamps!!!
	//go back into the movement history and find the movement previous to the states timestamp.
	//using that movement location, rotation and velocities, calculate the next movement with the states of aBunchOfStates
	//take the next move (the one that would come after the states timestamp), set the aBunchOfStates as the movement states.
	//Set the movement as the one calculated.
	//
	//Start the loop (from the move that follows until the current movement in history):
	//if the movement type is SendOrReceive, keep the states as is.
	//if the movement type is routine (but only before the first SendOrReceive of the loop), overwrite the states with the ones on the previous movement.
	////(you could use a boolean to check if you can overwrite)
	//calculate the current movement using the current states and the movement of the previous move.
	//set the current movement in the structure.
	//advance to next movement.

	UE_LOG(LogTemp, Log, TEXT("\n\n ******** Starting Server synchronization ******** \n\n"));
	UE_LOG(LogTemp, Log, TEXT("\n\n ****** Current Move: ****** \n %s \n\n"), *movementHistory[0].ToString());
	
	int historyMoment = closestIndexTo(aBunchOfStates.timestamp);
	if(historyMoment != movementHistory.size())
	{
		UE_LOG(LogTemp, Log, TEXT("movement history number before history reshape: %s"), *FString::FromInt(historyMoment));
		if(historyMoment <= 0)
		{
			movementHistory[0].timestampedStates.motorStateClass = aBunchOfStates.motorStateClass;
			movementHistory[0].timestampedStates.steerStateClass = aBunchOfStates.steerStateClass;
			movementHistory[0].type = EMovementType::sendOrReceive;
			establishMovementForTheClientFrom(historyMoment, aBunchOfStates.timestamp);//save moment to send to the client...
		}
		else
		{
			if(historyMoment >=0)
			{
				movementHistory[historyMoment].timestampedStates.motorStateClass = aBunchOfStates.motorStateClass;
				movementHistory[historyMoment].timestampedStates.steerStateClass = aBunchOfStates.steerStateClass;
				movementHistory[historyMoment].type = EMovementType::sendOrReceive;
				UE_LOG(LogTemp, Log, TEXT("movement history number to start reshaping: %s"), *FString::FromInt(historyMoment));
				UE_LOG(LogTemp, Log, TEXT("\n** Base move to start reshaping: ** \n %s\n"), *movementHistory[historyMoment].ToString());
				reshapeHistoryFrom(historyMoment, true);//chain reaction of history rewrite
				establishMovementForTheClientFrom(historyMoment, aBunchOfStates.timestamp);//save moment to send to the client...
			}
		}
		//send movement to client. If the jets calls it, it could be that the history moment was the same as the movement history size and it will return an invalid movement.
	}
	UE_LOG(LogTemp, Log, TEXT("\n\n ******** Server synchronization Finalized ******** \n\n"));
	UE_LOG(LogTemp, Log, TEXT("\n\n ****** Final server Move: ****** \n %s \n\n"), *movementHistory[0].ToString());
}

void UDeloreanReplicationMachine::synchronizeMovementHistoryWith(FMovementData aMovementStructure)
{
	//never change timestamps!!!
	//go back into the movement history and find the movement following (in time) the movement structure parameter.
	//calculate the time delta (in milliseconds) and transform it to seconds.
	//Calculate the movement that would be made on that time delta utilizing the movement structure parameter.
	//Set the calculated movement structure (including its states) as the movement following it.
	//
	//Start the loop (from the move that follows until the current movement in history):
	//if the movement type is SendOrReceive, keep the states as is.
	//if the movement type is routine (but only before the first SendOrReceive of the loop), overwrite the states with the ones on the previous movement.
	////(you could use a boolean to check if you can overwrite)
	//calculate the current movement using the current states and the movement of the previous move.
	//set the current movement in the structure.
	//advance to next movement.

	UE_LOG(LogTemp, Log, TEXT("\n\n ******** Starting Client synchronization ******** \n\n"));
	UE_LOG(LogTemp, Log, TEXT("\n\n ****** Current Move: ****** \n %s \n\n"), *movementHistory[0].ToString());
	
	int historyMoment = closestIndexTo(aMovementStructure.timestampedStates.timestamp);
	if(historyMoment != movementHistory.size())
	{
		UE_LOG(LogTemp, Log, TEXT("movement history number before history reshape: %s"), *FString::FromInt(historyMoment));
		if(historyMoment >=0)// >0, otherwise it will attempt to reshape the movement -1
		{
			UE_LOG(LogTemp, Log, TEXT("movement history number to start reshaping: %s"), *FString::FromInt(historyMoment));
			movementHistory[historyMoment].copyMovesFrom(aMovementStructure);
			reshapeHistoryFrom(historyMoment, false);//chain reaction of history rewrite
		}
	}
	UE_LOG(LogTemp, Log, TEXT("\n\n ******** Client synchronization Finalized ******** \n\n"));
	UE_LOG(LogTemp, Log, TEXT("\n\n ****** Final client Move: ****** \n %s \n\n"), *movementHistory[0].ToString());
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
			UE_LOG(LogTemp, Log, TEXT("\n changing states \n"));
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

		//align velocity!!! only if left or right steering == not center steering...
		if(needsToAlign)
		{
			UE_LOG(LogTemp, Log, TEXT("\n aligning velocity \n"));
			needsToAlign = false;
			float timeBetweenMovements = (nextMovementInHistory.timestampedStates.timestamp - currentMovementInHistory.timestampedStates.timestamp) / 1000.0f;
			nextMovementInHistory.linearVelocity += (steerCounterAcceleration + steerAlignAcceleration) * timeBetweenMovements;
			nextMovementInHistory.location = currentMovementInHistory.location + nextMovementInHistory.linearVelocity * timeBetweenMovements;
		}
		
		if(currentMovementInHistory.timestampedStates.steerStateClass != UCenterSteerState::StaticClass())
		{
			UE_LOG(LogTemp, Log, TEXT("\n needs to align velocity \n"));
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

	FVector sumOfAngularAccelerations = FVector(0);
	sumOfAngularAccelerations += owningJet->angularAccelerationGeneratedByAntiGravity();
	sumOfAngularAccelerations += Cast<USteerState, UObject>(aPreviousMovement.timestampedStates.steerStateClass->ClassDefaultObject)->angularAccelerationGeneratedTo(owningJet);

	FVector sumOfLinearAccelerations = FVector(0);
	sumOfLinearAccelerations += Cast<UMotorState, UObject>(aPreviousMovement.timestampedStates.motorStateClass->ClassDefaultObject)->linearAccelerationsGeneratedTo(owningJet);
	sumOfLinearAccelerations += retrieveTrackMagnetizationLinearAcceleration();

	if(simulationDuration == 0)
	{
		simulationDuration = GetWorld()->GetDeltaSeconds();
	}

	float effectiveLinearDamping = 1 - owningJet->linearDamping() * simulationDuration;
	float effectiveAngularDamping = 1 - owningJet->angularDamping() * simulationDuration;

	UE_LOG(LogTemp, Log, TEXT("effective linear damping %f"), effectiveLinearDamping);
	UE_LOG(LogTemp, Log, TEXT("effective angular damping %f"), effectiveAngularDamping);
	
	sumOfLinearAccelerations *=  effectiveLinearDamping;
	sumOfAngularAccelerations *= effectiveAngularDamping;

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

	UE_LOG(LogTemp, Log, TEXT("\n simulated movement: \n %s \n"), *simulatedMove.ToString());
	UE_LOG(LogTemp, Log, TEXT(">>angular velocity delta: %s"), *P2UVector(angularVelocityDelta).ToString());
	UE_LOG(LogTemp, Log, TEXT(">>angular velocity delta 'in radians': %s\n"), *FVector::DegreesToRadians(P2UVector(angularVelocityDelta)).ToString());
	
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