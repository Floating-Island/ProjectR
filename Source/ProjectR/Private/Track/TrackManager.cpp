// Fill out your copyright notice in the Description page of Project Settings.


#include "Track/TrackManager.h"

// Sets default values
ATrackManager::ATrackManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	trackGenerator = nullptr;
}

// Called when the game starts or when spawned
void ATrackManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATrackManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

