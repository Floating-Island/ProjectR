// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Jet/MotorStates/MotorState.h"
#include "Jet/Jet.h"
#include "MotorStateManager.generated.h"

class UMotorDriveComponent;

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
	FMovementData updatedDataSynchronizedWith(FStateData aBunchOfStates);

	UPROPERTY()
		AJet* owningJet;
	
	UPROPERTY()
		UMotorState* motorState;

	UFUNCTION(Server, Reliable, WithValidation)
		void serverUpdateMovementBasedOn(FStateData aBunchOfStates);

	UFUNCTION(NetMulticast, Reliable)
		void multicastSynchronizeMovementWith(FMovementData aMovementStructure);
	
	template<class aMotorStateType>
	void updateStateTo();

	template<class aMotorStateType>
	bool motorStateIsOfType();

	template<class aMotorStateType>
	void makeMotorStateBe();
	
public:
	virtual void PostInitializeComponents() override;
	
	void accelerate();
	void brake();
	void neutralize();
	void mix();

	void activate(UMotorDriveComponent* aMotorDrive);
	UClass* stateClass();
	void overrideStateTo(UClass* anotherState, AJet* owner);
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

template <class aMotorStateType>
void AMotorStateManager::makeMotorStateBe()
{
	if (IsValid(motorState) && motorStateIsOfType<aMotorStateType>())
	{
		return;
	}
	updateStateTo<aMotorStateType>();
	FStateData localStates = owningJet->generateCurrentStateDataToSend();
	serverUpdateMovementBasedOn(localStates);
}
