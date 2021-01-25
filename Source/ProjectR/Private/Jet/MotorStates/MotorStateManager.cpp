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
}

// Called every frame
void AMotorStateManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMotorStateManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if(HasAuthority())
	{
		motorState = NewObject<UNeutralMotorState>(this, FName("UNeutralMotorState"));
	}
}

bool AMotorStateManager::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool hasReplicated = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

    if (motorState != nullptr)
    {
        hasReplicated |= Channel->ReplicateSubobject(motorState, *Bunch, *RepFlags);
    }

    return hasReplicated;
}

void AMotorStateManager::accelerate()
{
	if (motorState && motorStateIsOfType<UAcceleratingMotorState>())
	{
		return;
	}
	serverAccelerate();
}

void AMotorStateManager::brake()
{
	if (motorState && motorStateIsOfType<UReversingMotorState>())
	{
		return;
	}
	serverBrake();
}

void AMotorStateManager::neutralize()
{
	if (!motorState || !motorStateIsOfType<UNeutralMotorState>())
	{
		serverNeutralize();
	}
}

void AMotorStateManager::mix()
{
	updateStateTo<UMixedMotorState>();
}

void AMotorStateManager::activate(UMotorDriveComponent* aMotorDrive)
{
	if(motorState)
	{
		motorState->activate(aMotorDrive);
	}
}

void AMotorStateManager::serverAccelerate_Implementation()
{
	if (HasAuthority())
	{
		updateStateTo<UAcceleratingMotorState>();
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
		updateStateTo<UReversingMotorState>();
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
		updateStateTo<UNeutralMotorState>();
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
