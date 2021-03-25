// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/MotorStateManager.h"


#include "Jet/MotorStates/NeutralMotorState.h"
#include "Jet/MotorStates/AcceleratingMotorState.h"
#include "Jet/MotorStates/ReversingMotorState.h"
#include "Jet/MotorStates/MixedMotorState.h"
#include "Jet/Jet.h"

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
	owningJet = Cast<AJet, AActor>(GetOwner());
}

void AMotorStateManager::serverAccelerateBasedOn_Implementation(FStateData aBunchOfStates)
{
	owningJet->synchronizeMovementHistoryWith(aBunchOfStates);
	FMovementData updatedDataToSend = owningJet->retrieveCurrentMovementDataToSend();
	multicastAccelerateWith(updatedDataToSend);
}

bool AMotorStateManager::serverAccelerateBasedOn_Validate(FStateData aBunchOfStates)
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


void AMotorStateManager::multicastAccelerateWith_Implementation(FMovementData aMovementStructure)
{
	owningJet->synchronizeMovementHistoryWith(aMovementStructure);
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
	updateStateTo<UNeutralMotorState>();
}

void AMotorStateManager::accelerate()
{
	if (IsValid(motorState) && motorStateIsOfType<UAcceleratingMotorState>())
	{
		return;
	}
	updateStateTo<UAcceleratingMotorState>();
	FStateData localStates = owningJet->generateCurrentStateDataToSend();
	serverAccelerateBasedOn(localStates);
}

void AMotorStateManager::brake()
{
	if (IsValid(motorState) && motorStateIsOfType<UReversingMotorState>())
	{
		return;
	}
	updateStateTo<UReversingMotorState>();
	serverBrake();
}

void AMotorStateManager::neutralize()
{
	if (IsValid(motorState) && motorStateIsOfType<UNeutralMotorState>())
	{
		return;
	}
	updateStateTo<UNeutralMotorState>();
	serverNeutralize();
}

void AMotorStateManager::mix()
{
	if (IsValid(motorState) && motorStateIsOfType<UMixedMotorState>())
	{
		return;
	}
	updateStateTo<UMixedMotorState>();
	serverMix();
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
