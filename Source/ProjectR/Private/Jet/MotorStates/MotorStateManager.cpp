// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/MotorStateManager.h"


#include "Jet/MotorStates/NeutralMotorState.h"
#include "Jet/MotorStates/AcceleratingMotorState.h"
#include "Jet/MotorStates/ReversingMotorState.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AMotorStateManager::AMotorStateManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
	bAlwaysRelevant = true;
	motorState = nullptr;
}

// Called when the game starts or when spawned
void AMotorStateManager::BeginPlay()
{
	Super::BeginPlay();
	motorState = GetWorld()->SpawnActor<ANeutralMotorState>();
}

// Called every frame
void AMotorStateManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMotorStateManager::accelerate()
{
	if (motorState->isAccelerating())
	{
		return;
	}
	serverAccelerate();
}

void AMotorStateManager::brake()
{
	if (motorState->isReversing())
	{
		return;
	}
	serverBrake();
}

void AMotorStateManager::neutralize()
{
	if (motorState->isAccelerating() || motorState->isReversing())
	{
		serverNeutralize();
	}
}

void AMotorStateManager::serverAccelerate_Implementation()
{
	if (HasAuthority())
	{
		updateStateTo<AAcceleratingMotorState>();
	}
}

bool AMotorStateManager::serverAccelerate_Validate()
{
	return true;
}


void AMotorStateManager::serverBrake_Implementation()
{
	if(HasAuthority())
	{
		updateStateTo<AReversingMotorState>();
	}
}

bool AMotorStateManager::serverBrake_Validate()
{
	return true;
}

void AMotorStateManager::serverNeutralize_Implementation()
{
	if(HasAuthority())
	{
		updateStateTo<ANeutralMotorState>();
	}
}

bool AMotorStateManager::serverNeutralize_Validate()
{
	return true;
}

void AMotorStateManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMotorStateManager, motorState);
}
