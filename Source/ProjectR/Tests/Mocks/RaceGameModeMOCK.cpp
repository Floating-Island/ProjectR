// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceGameModeMOCK.h"

#include "Kismet/GameplayStatics.h"
#include "Track/TrackGenerator.h"
#include "LapPhases/InitialLapPhase.h"

void ARaceGameModeMOCK::StartPlay()
{
	Super::Super::StartPlay();

	gameWorld = GetWorld();
	AActor* soonToBeTrack = UGameplayStatics::GetActorOfClass(gameWorld, ATrackGenerator::StaticClass());
	track = Cast<ATrackGenerator, AActor>(soonToBeTrack);
	AActor* soonToBeInitialPhase = UGameplayStatics::GetActorOfClass(gameWorld, AInitialLapPhase::StaticClass());
	initialPhase = Cast<AInitialLapPhase, AActor>(soonToBeInitialPhase);

	stage = gameWorld->SpawnActor<ARaceStage>();
}
