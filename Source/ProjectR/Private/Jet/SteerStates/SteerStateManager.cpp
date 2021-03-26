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

void ASteerStateManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	updateStateTo<UCenterSteerState>();
}

// Called when the game starts or when spawned
void ASteerStateManager::BeginPlay()
{
	Super::BeginPlay();
	owningJet = Cast<AJet, AActor>(GetOwner());

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

void ASteerStateManager::overrideStateTo(UClass* anotherState, AJet* owner)
{
	if(owningJet == owner)
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

void ASteerStateManager::serverUpdateMovementBasedOn_Implementation(FStateData aBunchOfStates)
{
	multicastSynchronizeMovementWith(updatedDataSynchronizedWith(aBunchOfStates));
}

bool ASteerStateManager::serverUpdateMovementBasedOn_Validate(FStateData aBunchOfStates)
{
	return true;
}

void ASteerStateManager::multicastSynchronizeMovementWith_Implementation(FMovementData aMovementStructure)
{
	owningJet->synchronizeMovementHistoryWith(aMovementStructure);
}

FMovementData ASteerStateManager::updatedDataSynchronizedWith(FStateData aBunchOfStates)
{
	owningJet->synchronizeMovementHistoryWith(aBunchOfStates);
	return owningJet->retrieveCurrentMovementDataToSend();
}
