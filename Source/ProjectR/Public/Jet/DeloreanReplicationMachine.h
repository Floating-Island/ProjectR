// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <chrono>

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DeloreanReplicationMachine.generated.h"


class AJet;
USTRUCT()
struct FStateData
{
	GENERATED_BODY()
	UPROPERTY()
		int64 timestamp;
	UPROPERTY()
		UClass* motorStateClass;
	UPROPERTY()
		UClass* steerStateClass;

	FStateData()
	{
		timestamp = 0;
		motorStateClass = nullptr;
		steerStateClass = nullptr;
	}

	FStateData(UClass* classOfMotorState, UClass* classOfSteerState)
	{
		timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		motorStateClass = classOfMotorState;
		steerStateClass = classOfSteerState;
	}

	FString ToString() const
	{
		return FString("Movement timestamp: ") + FString::Printf(TEXT("%lld"), timestamp) + FString("\n") +
				FString("Motor state class: ") + FString(motorStateClass? motorStateClass->GetFName().ToString() : "nullptr") + FString("\n") +
				FString("Steer state class: ") + FString(steerStateClass? steerStateClass->GetFName().ToString() : "nullptr")
		;
	}
};

UENUM()
enum class EMovementType : uint8 {routine UMETA(DisplayName = "routine"), sendOrReceive UMETA(DisplayName = "sendOrReceive") };

USTRUCT()
struct FMovementData
{
	GENERATED_BODY()

	UPROPERTY()
		FStateData timestampedStates;
	UPROPERTY()
		FVector location;
	UPROPERTY()
		FRotator rotation;
	UPROPERTY()
		FVector linearVelocity;
	UPROPERTY()
		FVector angularVelocityInRadians;
	UPROPERTY()
		EMovementType type;

	FMovementData()
	{
		timestampedStates = FStateData();
		location = FVector(0);
		rotation = FRotator(0);
		linearVelocity = FVector(0);
		angularVelocityInRadians = FVector(0);
		type = EMovementType::routine;
	}
	
	FMovementData(AActor* actor, EMovementType movementType, UClass* classOfMotorState, UClass* classOfSteerState)
	{
		timestampedStates = FStateData(classOfMotorState, classOfSteerState);
		location = actor->GetActorLocation();
		rotation = actor->GetActorRotation();
		linearVelocity = Cast<UPrimitiveComponent, UActorComponent>(actor->GetRootComponent())->GetPhysicsLinearVelocity();
		angularVelocityInRadians = Cast<UPrimitiveComponent, UActorComponent>(actor->GetRootComponent())->GetPhysicsAngularVelocityInRadians();
		type = movementType;
	}

	FString ToString() const
	{
		return FString("Movement Data:\n") + 
			FString("Movement type: ") + FString(StaticEnum<EMovementType>()->GetValueAsString(type)) + FString("\n") +
			timestampedStates.ToString() + FString("\n") +
			FString("Location: ") + location.ToString() + FString("\n") +
			FString("Linear velocity: ") + linearVelocity.ToString() + FString("\n") +
			FString("Rotation: ") + rotation.ToString() + FString("\n") +
			FString("Angular velocity in radians: ") + angularVelocityInRadians.ToString()
		;
	}

	/**copies everything from anotherMovement except the timestampedStates timestamp*/
	void regenerateMoveFrom(FMovementData anotherMovement, EMovementType aNewMovementType)
	{
		location = anotherMovement.location;
		rotation = anotherMovement.rotation;
		linearVelocity = anotherMovement.linearVelocity;
		angularVelocityInRadians = anotherMovement.angularVelocityInRadians;
		timestampedStates.motorStateClass = anotherMovement.timestampedStates.motorStateClass;
		timestampedStates.steerStateClass = anotherMovement.timestampedStates.steerStateClass;
		type = aNewMovementType;
	}

	/**copies movements from anotherMovement except the timestampedStates*/
	void copyMovesFrom(FMovementData anotherMovement)
	{
		location = anotherMovement.location;
		rotation = anotherMovement.rotation;
		linearVelocity = anotherMovement.linearVelocity;
		angularVelocityInRadians = anotherMovement.angularVelocityInRadians;
	}
};








/**
 * Class responsible to synchronize data sent to and received from the server.
 * Has a movement history used to re simulate past movements until the present.
 * It rewrites a jet's history.
 */
UCLASS()
class PROJECTR_API UDeloreanReplicationMachine : public UObject
{
	GENERATED_BODY()

private:
	AJet* owningJet;
	bool generateSendOrReceiveMovementType;
	FMovementData synchronizedMovement;
	bool readyToEstablishMovement;

protected:
	/** don't add objects directly, use addMovementToHistory instead.*/
	std::deque<FMovementData> movementHistory;

	/**With 60 we will have 1000 milliseconds of movements into the past
	 * (assuming 60fps).
	 * this information is also available in the jet header.
	 */
	int movementHistorySize;
	
	void changeHistoryMovementAtMomentWith(FStateData aBunchOfStates, int atHistoryMoment);

	void reshapeHistoryFrom(int aMomentInHistory, bool anOptionToChangeStates);

	FMovementData simulateNextMovementFrom(const FMovementData& aPreviousMovement, float simulationDuration = 0);
	
	void calculateNextMovementChangesTo(FVector& aSumOfLinearAccelerations, FVector& aSumOfAngularAccelerations,
	                                    float& aSimulationDuration, const FMovementData& aPreviousMovement);
	
	void calculatePhysicsBodyChangesTo(PxVec3& aLinearVelocityDelta, PxVec3& anANgularVelocityDelta,
	                                   const float& simulationDuration,
	                                   const FVector& aSumOfLinearAccelerations, const FVector& aSumOfAngularAccelerations);

	FMovementData generateSimulatedMoveFrom(const FMovementData& aPreviousMovement, FVector aLinearVelocityDelta, FVector anAngularVelocityDelta, float aSimulationDuration);

	void addToMovementHistory(FMovementData aMovement);

	int closestIndexTo(int64 aTimestamp);

	void copyCurrentMovementStatesToNextIf(bool& needsToChangeStates, FMovementData& aCurrentMovementInHistory,
	                                 FMovementData& aNextMovementInHistory);
	
	void manageVelocityAlignmentWhen(bool& needsToAlign, FVector& aSteerCounterAcceleration,
	                                  FVector& aSteerAlignAcceleration,
	                                  FMovementData& aCurrentMovementInHistory, FMovementData& aNextMovementInHistory);

	void establishMovementForTheClientFrom(int aMomentInHistory, int64 aClientTimestamp);

	void smoothFinalMovementFrom(FMovementData initialMovement, int64 aTimestamp);
	
public:
	UDeloreanReplicationMachine();
	
	UFUNCTION()
		void addMovementToHistory();

	FStateData generateCurrentStateDataToSend();

	FMovementData retrieveCurrentMovementDataToSend();

	/**Normally executed by the server.
	*Looks for the nearest local movement using the aBunchOfStates timestamp.
	*It copies the received states to the nearest movement found and starts to resimulate its movements from there (only if history moment > 0).
	*Then it saves the closest move near to the timestamp received to the client, with the timestamp and states received.
	*/
	void synchronizeMovementHistoryWith(FStateData aBunchOfStates);

	/**Normally executed by the client.
	*Looks for the nearest local movement using the aMovementStructure timestamp.
	*It copies the received moves to the movement with that same timestamp and starts to resimulate its movements from there (only if history moment >= 0).
	*Finally, it tries to smooth the initial current move to the final one simulated.
	*/
	void synchronizeMovementHistoryWith(FMovementData aMovementStructure);


	void setDefaultVariablesTo(AJet* anOwner, int aMovementHistorySize);

	bool hasDataForClient();
};
