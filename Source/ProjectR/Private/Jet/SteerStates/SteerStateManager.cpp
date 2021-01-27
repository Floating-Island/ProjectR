// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/SteerStates/SteerStateManager.h"

#include "Jet/SteerStates/CenterSteerState.h"

// Sets default values
ASteerStateManager::ASteerStateManager()
{
	PrimaryActorTick.bCanEverTick = false;
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
	if(steerState && steerStateIsOfType<USteerLeftState>())
	{
		return;
	}
	updateStateTo<USteerLeftState>();
}
