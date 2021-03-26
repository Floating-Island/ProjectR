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
	SetReplicates(true);
	bAlwaysRelevant = true;
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
	if (IsValid(motorState))
	{
		motorState->activate(aMotorDrive);
	}
}

UClass* AMotorStateManager::stateClass()
{
	if(IsValid(motorState))
	{
		return motorState->GetClass();
	}
	return nullptr;
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

void AMotorStateManager::serverUpdateMovementBasedOn_Implementation(FStateData aBunchOfStates)
{
	multicastSynchronizeMovementWith(updatedDataSynchronizedWith(aBunchOfStates));
}

bool AMotorStateManager::serverUpdateMovementBasedOn_Validate(FStateData aBunchOfStates)
{
	return true;
}

FMovementData AMotorStateManager::updatedDataSynchronizedWith(FStateData aBunchOfStates)
{
	owningJet->synchronizeMovementHistoryWith(aBunchOfStates);
	return owningJet->retrieveCurrentMovementDataToSend();
}

void AMotorStateManager::multicastSynchronizeMovementWith_Implementation(FMovementData aMovementStructure)
{
	owningJet->synchronizeMovementHistoryWith(aMovementStructure);
}
