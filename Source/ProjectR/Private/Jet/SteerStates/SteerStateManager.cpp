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
}

void ASteerStateManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	updateStateTo<UCenterSteerState>();
	owningJet = Cast<AJet, AActor>(GetOwner());
}

// Called when the game starts or when spawned
void ASteerStateManager::BeginPlay()
{
	Super::BeginPlay();
}

void ASteerStateManager::activate(USteeringComponent* aSteeringDrive)
{
	steerState->activate(aSteeringDrive);
}

UClass* ASteerStateManager::stateClass()
{
	return steerState->GetClass();
}

void ASteerStateManager::overrideStateTo(UClass* anotherState, AJet* anOwningJet)
{
	if(owningJet == anOwningJet)
	{
		steerState = nullptr;
		steerState = NewObject<USteerState>(this, anotherState, anotherState->GetFName());
	}
}

void ASteerStateManager::steerLeft()
{
	makeSteerStateBe<ULeftSteerState>();
}

void ASteerStateManager::center()
{
	makeSteerStateBe<UCenterSteerState>();
}

void ASteerStateManager::steerRight()
{
	makeSteerStateBe<URightSteerState>();
}
