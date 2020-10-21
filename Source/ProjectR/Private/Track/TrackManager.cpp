// Fill out your copyright notice in the Description page of Project Settings.


#include "Track/TrackManager.h"
#include "Track/TrackGenerator.h"

// Sets default values
ATrackManager::ATrackManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
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

void ATrackManager::PostActorCreated()
{
	Super::PostActorCreated();
	if(trackGenerator == nullptr)
	{
		trackGenerator = GetWorld()->SpawnActor<ATrackGenerator>(ATrackGenerator::StaticClass());
		trackGenerator->AttachToActor(this,FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
		UE_LOG(LogTemp, Log, TEXT("the track manager: %s a root component set."), *FString(GetRootComponent() != nullptr ? "has" : "doesn't have"));
	}
}

