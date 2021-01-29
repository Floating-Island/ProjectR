// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SteerState.h"
#include "GameFramework/Actor.h"
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

	TWeakObjectPtr<USteerState> steerState;

	template<class aSteerStateType>
	bool steerStateIsOfType();

	template<class aSteerStateType>
	void updateStateTo();

	UFUNCTION(Server, Reliable, WithValidation)
		void serverSteerLeft();

	UFUNCTION(Server, Reliable, WithValidation)
		void serverSteerRight();

	UFUNCTION(Server, Reliable, WithValidation)
		void serverCenter();
	
	UFUNCTION(NetMulticast, Reliable)
		void multicastSteerLeft();

	UFUNCTION(NetMulticast, Reliable)
		void multicastSteerRight();

	UFUNCTION(NetMulticast, Reliable)
		void multicastCenter();

public:
	virtual void PostInitializeComponents() override;
	
	void steerLeft();
	void steerRight();
	void center();
	void activate(USteeringComponent* aSteeringDrive);
};

template <class aSteerStateType>
bool ASteerStateManager::steerStateIsOfType()
{
	return steerState->IsA(aSteerStateType::StaticClass()) ? true : false;
}

template <class aSteerStateType>
void ASteerStateManager::updateStateTo()
{
	if(IsValid(steerState.Get()) && steerStateIsOfType<aSteerStateType>())
	{
		return;
	}
	steerState = NewObject<aSteerStateType>(this, aSteerStateType::StaticClass()->GetFName());
}
