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

protected:
		/** don't add objects directly, use addMovementToHistory instead.*/
	std::deque<FMovementData> movementHistory;

	/**With 60 we will have 1000 milliseconds of movements into the past
	 * (assuming 60fps).
	 * this information is also available in the jet header.
	 */
	int movementHistorySize;



	FMovementData createMovementHistoryRevisionWith(FMovementData aBaseMovement, FStateData aStatesBase);
	FMovementData createMovementHistoryRevisionWith(FMovementData aBaseMovement, float aTimeDelta);

	void reshapeHistoryFrom(int aMomentInHistory);

	FMovementData simulateNextMovementFrom(FMovementData aPreviousMovement, float simulationDuration = 0);

	FVector retrieveTrackMagnetizationLinearAcceleration();

	void addToMovementHistory(FMovementData aMovement);
	
public:
	UDeloreanReplicationMachine();
	
	UFUNCTION()
		void addMovementToHistory();

	FStateData generateCurrentStateDataToSend();

	FMovementData retrieveCurrentMovementDataToSend();

	void synchronizeMovementHistoryWith(FStateData aBunchOfStates);
	void synchronizeMovementHistoryWith(FMovementData aMovementStructure);


	void setDefaultVariablesTo(AJet* anOwner, int aMovementHistorySize);
};
