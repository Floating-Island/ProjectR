// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/SteerStates/SteerStateManager.h"

// Sets default values
ASteerStateManager::ASteerStateManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASteerStateManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASteerStateManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

