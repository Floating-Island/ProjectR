// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/MotorState.h"


// Sets default values
AMotorState::AMotorState()
{
	PrimaryActorTick.bCanEverTick = false;
	SetReplicates(true);//make test.
	bAlwaysRelevant = true;//make test.
}

// Called when the game starts or when spawned
void AMotorState::BeginPlay()
{
	Super::BeginPlay();
}

