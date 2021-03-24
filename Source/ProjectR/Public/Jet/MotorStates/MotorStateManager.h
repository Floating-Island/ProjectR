// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Jet/MotorStates/MotorState.h"
#include "MotorStateManager.generated.h"

struct FMovementData;
struct FStateData;
class UMotorDriveComponent;
class AJet;

UCLASS()
class PROJECTR_API AMotorStateManager : public AActor
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	AMotorStateManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	AJet* owningJet;
	
	UPROPERTY()
		UMotorState* motorState;

	UFUNCTION(Server, Reliable, WithValidation)
		void serverAccelerateBasedOn(FStateData aBunchOfStates);

	UFUNCTION(Server, Reliable, WithValidation)
		void serverBrake();

	UFUNCTION(Server, Reliable, WithValidation)
		void serverNeutralize();

	UFUNCTION(Server, Reliable, WithValidation)
		void serverMix();

	UFUNCTION(NetMulticast, Reliable)
		void multicastAccelerateWith(FMovementData aMovementStructure);

	UFUNCTION(NetMulticast, Reliable)
		void multicastBrake();

	UFUNCTION(NetMulticast, Reliable)
		void multicastNeutralize();

	UFUNCTION(NetMulticast, Reliable)
		void multicastMix();

	
	
	template<class aMotorStateType>
	void updateStateTo();

	template<class aMotorStateType>
	bool motorStateIsOfType();
	
public:
	virtual void PostInitializeComponents() override;
	
	void accelerate();
	void brake();
	void neutralize();
	void mix();

	void activate(UMotorDriveComponent* aMotorDrive);
	UClass* stateClass();
};

template <class aMotorStateType>
void AMotorStateManager::updateStateTo()
{
	if(IsValid(motorState) && motorStateIsOfType<aMotorStateType>())
	{
		return;
	}
	
	motorState = nullptr;
	motorState = NewObject<aMotorStateType>(this, aMotorStateType::StaticClass()->GetFName());
}

template <class aMotorStateType>
bool AMotorStateManager::motorStateIsOfType()
{
	return motorState->IsA(aMotorStateType::StaticClass()) ? true : false;
}
