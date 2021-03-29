// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/MotorStateManager.h"


#include "Jet/MotorStates/NeutralMotorState.h"
#include "Jet/MotorStates/AcceleratingMotorState.h"
#include "Jet/MotorStates/ReversingMotorState.h"
#include "Jet/MotorStates/MixedMotorState.h"

// Sets default values
AMotorStateManager::AMotorStateManager()
{
	PrimaryActorTick.bCanEverTick = false;
	motorState = nullptr;
}

void AMotorStateManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	updateStateTo<UNeutralMotorState>();
}

// Called when the game starts or when spawned
void AMotorStateManager::BeginPlay()
{
	Super::BeginPlay();
	owningJet = Cast<AJet, AActor>(GetOwner());
}

void AMotorStateManager::activate(UMotorDriveComponent* aMotorDrive)
{
	motorState->activate(aMotorDrive);
}

UClass* AMotorStateManager::stateClass()
{
	return motorState->GetClass();
}

void AMotorStateManager::overrideStateTo(UClass* anotherState, AJet* owner)
{
	if(owningJet == owner)
	{
		motorState = nullptr;
		motorState = NewObject<UMotorState>(this, anotherState, anotherState->GetFName());
	}
}

void AMotorStateManager::accelerate()
{
	makeMotorStateBe<UAcceleratingMotorState>();
}

void AMotorStateManager::brake()
{
	makeMotorStateBe<UReversingMotorState>();
}

void AMotorStateManager::neutralize()
{
	makeMotorStateBe<UNeutralMotorState>();
}

void AMotorStateManager::mix()
{
	makeMotorStateBe<UMixedMotorState>();
}
