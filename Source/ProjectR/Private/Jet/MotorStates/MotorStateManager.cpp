// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/MotorStateManager.h"


#include "Jet/MotorStates/NeutralMotorState.h"
#include "Jet/MotorStates/AcceleratingMotorState.h"
#include "Jet/MotorStates/ReversingMotorState.h"

// Sets default values
AMotorStateManager::AMotorStateManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
	AMotorState* oldState = motorState;
	motorState = GetWorld()->SpawnActor<AAcceleratingMotorState>();
	oldState->Destroy();
}

void AMotorStateManager::brake()
{
	AMotorState* oldState = motorState;
	motorState = GetWorld()->SpawnActor<AReversingMotorState>();
	oldState->Destroy();
}

void AMotorStateManager::neutralize()
{
	AMotorState* oldState = motorState;
	motorState = GetWorld()->SpawnActor<ANeutralMotorState>();
	oldState->Destroy();
}

