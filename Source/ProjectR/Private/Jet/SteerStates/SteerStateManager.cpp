// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/SteerStates/SteerStateManager.h"

#include "Jet/SteerStates/CenterSteerState.h"
#include "Jet/SteerStates/RightSteerState.h"
#include "Jet/SteerStates/LeftSteerState.h"


// Sets default values
ASteerStateManager::ASteerStateManager()
{
	PrimaryActorTick.bCanEverTick = false;
	steerState = nullptr;
	SetReplicates(true);
	bAlwaysRelevant = true;
}

// Called when the game starts or when spawned
void ASteerStateManager::BeginPlay()
{
	Super::BeginPlay();
}

void ASteerStateManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	steerState = NewObject<UCenterSteerState>(this, FName("UCenterSteerState"));
}

void ASteerStateManager::steerLeft()
{
	if(steerState && steerStateIsOfType<ULeftSteerState>())
	{
		return;
	}
	updateStateTo<ULeftSteerState>();
}

void ASteerStateManager::steerRight()
{
	if(steerState && steerStateIsOfType<URightSteerState>())
	{
		return;
	}
	updateStateTo<URightSteerState>();
}

void ASteerStateManager::center()
{
	if(steerState && steerStateIsOfType<UCenterSteerState>())
	{
		return;
	}
	updateStateTo<UCenterSteerState>();
}
