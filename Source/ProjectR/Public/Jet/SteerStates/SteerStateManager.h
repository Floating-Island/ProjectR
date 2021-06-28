// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "SteerState.h"
#include "Jet/Jet.h"
#include "SteerStateManager.generated.h"


UCLASS()
class PROJECTR_API ASteerStateManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASteerStateManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
		USteerState* steerState;

	UPROPERTY()
		AJet* owningJet;

	template<class aSteerStateType>
	bool steerStateIsOfType();

	template<class aSteerStateType>
	void updateStateTo();

	template<class aSteerStateType>
	void makeSteerStateBe();

public:
	virtual void PostInitializeComponents() override;
	
	void steerLeft();
	void steerRight();
	void center();
	void activate(USteeringComponent* aSteeringDrive);

	UClass* stateClass();
	void overrideStateTo(UClass* anotherState, AJet* anOwningJet);
};

template <class aSteerStateType>
bool ASteerStateManager::steerStateIsOfType()
{
	return steerState->IsA(aSteerStateType::StaticClass()) ? true : false;
}

template <class aSteerStateType>
void ASteerStateManager::updateStateTo()
{	
	steerState = nullptr;
	steerState = NewObject<aSteerStateType>(this, aSteerStateType::StaticClass()->GetFName());
}

template <class aSteerStateType>
void ASteerStateManager::makeSteerStateBe()
{
	if (IsValid(steerState) && steerStateIsOfType<aSteerStateType>())
	{
		return;
	}
	updateStateTo<aSteerStateType>();
	owningJet->sendMovementToServerRequestedBy(this);
}
