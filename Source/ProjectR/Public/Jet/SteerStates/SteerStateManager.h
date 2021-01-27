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
	virtual void PostInitializeComponents() override;

	USteerState* steerState;

	template<class aSteerStateType>
	bool steerStateIsOfType();

	template<class aSteerStateType>
	void updateStateTo();

	template<class aSteerStateType>
	void checkCurrentStateAndUpdateTo();

	

public:
	void steerLeft();

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

template <class aSteerStateType>
void ASteerStateManager::checkCurrentStateAndUpdateTo()
{
	if(steerState && steerStateIsOfType<aSteerStateType>())
	{
		return;
	}
	updateStateTo<aSteerStateType>();
}
