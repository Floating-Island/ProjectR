// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SteerState.h"
#include "GameFramework/Actor.h"
#include "SteerStateManager.generated.h"

class USteerState;
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

	UPROPERTY(Replicated)
		USteerState* steerState;

	template<class aSteerStateType>
	bool steerStateIsOfType();

	template<class aSteerStateType>
	void updateStateTo();

	UFUNCTION(Server, Reliable, WithValidation)
		void serverSteerLeft();

	UFUNCTION(Server, Reliable, WithValidation)
		void serverSteerRight();

public:
	virtual void PostInitializeComponents() override;
	virtual bool ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	
	void steerLeft();
	void steerRight();
	void center();

};

template <class aSteerStateType>
bool ASteerStateManager::steerStateIsOfType()
{
	return steerState->GetClass() == aSteerStateType::StaticClass() ? true : false;
}

template <class aSteerStateType>
void ASteerStateManager::updateStateTo()
{
	if(!steerState || !steerStateIsOfType<aSteerStateType>())
	{
		steerState = NewObject<aSteerStateType>(this, aSteerStateType::StaticClass()->GetFName());
	}
}
