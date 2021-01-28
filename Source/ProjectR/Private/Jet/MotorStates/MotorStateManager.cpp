// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/MotorStateManager.h"


#include "Jet/MotorStates/NeutralMotorState.h"
#include "Jet/MotorStates/AcceleratingMotorState.h"
#include "Jet/MotorStates/ReversingMotorState.h"
#include "Jet/MotorStates/MixedMotorState.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

// Sets default values
AMotorStateManager::AMotorStateManager()
{
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(true);
	bAlwaysRelevant = true;
	motorState = nullptr;
}

// Called when the game starts or when spawned
void AMotorStateManager::BeginPlay()
{
	Super::BeginPlay();
}

void AMotorStateManager::serverAccelerate_Implementation()
{
	multicastAccelerate();
}

bool AMotorStateManager::serverAccelerate_Validate()
{
	return true;
}

void AMotorStateManager::serverBrake_Implementation()
{
	multicastBrake();
}

bool AMotorStateManager::serverBrake_Validate()
{
	return true;
}

void AMotorStateManager::serverNeutralize_Implementation()
{
	multicastNeutralize();
}

bool AMotorStateManager::serverNeutralize_Validate()
{
	return true;
}

void AMotorStateManager::serverMix_Implementation()
{
	multicastMix();
}

bool AMotorStateManager::serverMix_Validate()
{
	return true;
}


void AMotorStateManager::multicastAccelerate_Implementation()
{
	updateStateTo<UAcceleratingMotorState>();
}

void AMotorStateManager::multicastBrake_Implementation()
{
	updateStateTo<UReversingMotorState>();
}

void AMotorStateManager::multicastNeutralize_Implementation()
{
	updateStateTo<UNeutralMotorState>();
}

void AMotorStateManager::multicastMix_Implementation()
{
	updateStateTo<UMixedMotorState>();
}

void AMotorStateManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (HasAuthority())
	{
		serverNeutralize();
	}
}

void AMotorStateManager::accelerate()
{
	if (motorState.Get() && motorStateIsOfType<UAcceleratingMotorState>())
	{
		return;
	}
	serverAccelerate();
}

void AMotorStateManager::brake()
{
	if (motorState.Get() && motorStateIsOfType<UReversingMotorState>())
	{
		return;
	}
	serverBrake();
}

void AMotorStateManager::neutralize()
{
	if (motorState.Get() && motorStateIsOfType<UNeutralMotorState>())
	{
		return;
	}
	serverNeutralize();
}

void AMotorStateManager::mix()
{
	if (motorState.Get() && motorStateIsOfType<UMixedMotorState>())
	{
		return;
	}
	serverMix();
}

void AMotorStateManager::activate(UMotorDriveComponent* aMotorDrive)
{
	if (motorState.Get())
	{
		motorState->activate(aMotorDrive);
	}
}