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

void ASteerStateManager::serverSteerLeft_Implementation()
{
	multicastSteerLeft();
}

bool ASteerStateManager::serverSteerLeft_Validate()
{
	return true;
}

void ASteerStateManager::serverSteerRight_Implementation()
{
	multicastSteerRight();
}

bool ASteerStateManager::serverSteerRight_Validate()
{
	return true;
}

void ASteerStateManager::serverCenter_Implementation()
{
	multicastCenter();
}

bool ASteerStateManager::serverCenter_Validate()
{
	return true;
}

void ASteerStateManager::multicastSteerLeft_Implementation()
{
	updateStateTo<ULeftSteerState>();
}

void ASteerStateManager::multicastSteerRight_Implementation()
{
	updateStateTo<URightSteerState>();
}

void ASteerStateManager::multicastCenter_Implementation()
{
	updateStateTo<UCenterSteerState>();
}

void ASteerStateManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	updateStateTo<UCenterSteerState>();
}

void ASteerStateManager::steerLeft()
{
	if(IsValid(steerState) && steerStateIsOfType<ULeftSteerState>())
	{
		return;
	}
	updateStateTo<ULeftSteerState>();
	serverSteerLeft();
}

void ASteerStateManager::steerRight()
{
	if(IsValid(steerState) && steerStateIsOfType<URightSteerState>())
	{
		return;
	}
	serverSteerRight();
}

void ASteerStateManager::center()
{
	if(IsValid(steerState) && steerStateIsOfType<UCenterSteerState>())
	{
		return;
	}
	serverCenter();
}

void ASteerStateManager::activate(USteeringComponent* aSteeringDrive)
{
	if(IsValid(steerState))
	{
		steerState->activate(aSteeringDrive);
	}
}

UClass* ASteerStateManager::stateClass()
{
	if(IsValid(steerState))
	{
		return steerState->GetClass();
	}
	return nullptr;
}
