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
}

void UDeloreanReplicationMachine::setDefaultVariablesTo(AJet* anOwner, int aMovementHistorySize)
{
	owningJet = anOwner;
	movementHistorySize = aMovementHistorySize;
	movementHistory = std::deque<FMovementData>(movementHistorySize, FMovementData());
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
	generateSendOrReceiveMovementType = true;
	return FMovementData(owningJet, EMovementType::sendOrReceive, owningJet->currentMotorStateClass(), owningJet->currentSteerStateClass());
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
	
	int historyMoment = 0;
	if(aBunchOfStates.timestamp < movementHistory[0].timestampedStates.timestamp)//check that the states don't come from the future...
	{
		while (historyMoment < movementHistory.size())
		{
			if(movementHistory[historyMoment].timestampedStates.timestamp <= aBunchOfStates.timestamp)//we found the moment previous to the received states...
			{
				break;
			}
			++historyMoment;
		}
	}
	if(historyMoment != movementHistory.size())
	{
		FMovementData historyRevisionStart = createMovementHistoryRevisionWith(movementHistory[historyMoment], aBunchOfStates);
		--historyMoment;//historyMoment is previous to --historyMoment
		if(historyMoment >=0)
		{
			movementHistory[historyMoment].regenerateMoveFrom(historyRevisionStart, historyRevisionStart.type);
			reshapeHistoryFrom(historyMoment);//chain reaction of history rewrite
		}
	}
	UE_LOG(LogTemp, Log, TEXT("\n\n ******** Server synchronization Finalized ******** \n\n"));
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
	
	int historyMoment = 0;
	if(aMovementStructure.timestampedStates.timestamp < movementHistory[0].timestampedStates.timestamp)//check that the movement don't come from the future...
	{
		while (historyMoment < movementHistory.size())
		{
			if(movementHistory[historyMoment].timestampedStates.timestamp <= aMovementStructure.timestampedStates.timestamp)//we found the moment previous to the received movement...
			{
				break;
			}
			++historyMoment;
		}
	}
	if(historyMoment != movementHistory.size())
	{
		--historyMoment;//go to a more recent movement...
		if(historyMoment >=0)
		{
			float timeBetweenMovements = (movementHistory[historyMoment].timestampedStates.timestamp - aMovementStructure.timestampedStates.timestamp) / 1000.0f;
			FMovementData historyRevisionStart = createMovementHistoryRevisionWith(aMovementStructure, timeBetweenMovements);
			movementHistory[historyMoment].regenerateMoveFrom(historyRevisionStart, historyRevisionStart.type);
			reshapeHistoryFrom(historyMoment);//chain reaction of history rewrite
		}
	}
	UE_LOG(LogTemp, Log, TEXT("\n\n ******** Client synchronization Finalized ******** \n\n"));
}


FMovementData UDeloreanReplicationMachine::createMovementHistoryRevisionWith(FMovementData aBaseMovement, FStateData aStatesBase)
{
	aBaseMovement.timestampedStates.motorStateClass = aStatesBase.motorStateClass;
	aBaseMovement.timestampedStates.steerStateClass = aStatesBase.steerStateClass;

	FMovementData revisedMovement = FMovementData();

	revisedMovement = simulateNextMovementFrom(aBaseMovement);//calculate next movement with these values...

	return revisedMovement;
}

FMovementData UDeloreanReplicationMachine::createMovementHistoryRevisionWith(FMovementData aBaseMovement, float aTimeDelta)
{
	FMovementData revisedMovement = FMovementData();

	revisedMovement = simulateNextMovementFrom(aBaseMovement, aTimeDelta);//calculate next movement with these values using the time delta instead of the tick delta time...

	return revisedMovement;
}

void UDeloreanReplicationMachine::reshapeHistoryFrom(int aMomentInHistory)
{
	bool needsToChangeStates = true;

	FVector steerCounterAcceleration = FVector(0);
	FVector steerAlignAcceleration = FVector(0);
	bool needsToAlign = false;
	while(aMomentInHistory > 0)
	{
		FMovementData currentMovementInHistory = movementHistory[aMomentInHistory];
		FMovementData nextMovementInHistory = movementHistory[aMomentInHistory - 1];
		if(needsToChangeStates && nextMovementInHistory.type != EMovementType::sendOrReceive)
		{
			nextMovementInHistory.timestampedStates.motorStateClass = currentMovementInHistory.timestampedStates.motorStateClass;
			nextMovementInHistory.timestampedStates.steerStateClass = currentMovementInHistory.timestampedStates.steerStateClass;
		}
		else //found the first movement in history that was already sent or received from the server...
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