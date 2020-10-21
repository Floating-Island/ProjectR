// Fill out your copyright notice in the Description page of Project Settings.


#include "Track/TrackManager.h"
#include "Track/TrackGenerator.h"
#include "Kismet/GameplayStatics.h"


ATrackManager::ATrackManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATrackManager::BeginPlay()
{
	Super::BeginPlay();
	collectTrackGenerators();
}

void ATrackManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ATrackManager::collectTrackGenerators() {
  TArray<AActor*> spawnedGenerators = TArray<AActor*>();
  UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATrackGenerator::StaticClass(), spawnedGenerators);
  for (auto generator : spawnedGenerators)
  {
    ATrackGenerator* trackGenerator = Cast<ATrackGenerator, AActor>(generator);
    if (trackGenerator)
    {
      trackGeneratorSet.Add(trackGenerator);
    }
  }
}
