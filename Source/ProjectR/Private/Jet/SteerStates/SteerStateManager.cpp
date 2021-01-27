// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/SteerStates/SteerStateManager.h"

#include "Jet/SteerStates/CenterSteerState.h"
#include "Jet/SteerStates/RightSteerState.h"
#include "Jet/SteerStates/LeftSteerState.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

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
	if(HasAuthority())
	{
		updateStateTo<ULeftSteerState>();
	}
}

bool ASteerStateManager::serverSteerLeft_Validate()
{
	return true;
}

void ASteerStateManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if(HasAuthority())
	{
		steerState = NewObject<UCenterSteerState>(this, FName("UCenterSteerState"));
	}
}

bool ASteerStateManager::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool hasReplicated = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

    if (steerState != nullptr)
    {
        hasReplicated |= Channel->ReplicateSubobject(steerState, *Bunch, *RepFlags);
    }

    return hasReplicated;
}

void ASteerStateManager::steerLeft()
{
	if(steerState && steerStateIsOfType<ULeftSteerState>())
	{
		return;
	}
	serverSteerLeft();
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


void ASteerStateManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASteerStateManager, steerState);
}