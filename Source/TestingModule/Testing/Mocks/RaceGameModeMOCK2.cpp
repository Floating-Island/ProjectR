// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceGameModeMOCK2.h"

#include "Kismet/GameplayStatics.h"
#include "Track/TrackGenerator.h"
#include "LapPhases/InitialLapPhase.h"
#include "GameMode/RaceStages/RaceStage.h"
#include "ProjectR/Testing/Mocks/LapManagerMOCK.h"

void ARaceGameModeMOCK2::StartPlay()
{
	Super::Super::StartPlay();

	gameWorld = GetWorld();
	AActor* soonToBeTrack = UGameplayStatics::GetActorOfClass(gameWorld, ATrackGenerator::StaticClass());
	track = Cast<ATrackGenerator, AActor>(soonToBeTrack);
	AActor* soonToBeInitialPhase = UGameplayStatics::GetActorOfClass(gameWorld, AInitialLapPhase::StaticClass());
	initialPhase = Cast<AInitialLapPhase, AActor>(soonToBeInitialPhase);

	stage = gameWorld->SpawnActor<ARaceStage>();
}

void ARaceGameModeMOCK2::changeStageTo(ARaceStage* anotherStage)
{
	ARaceStage* oldStage = stage;
	stage = anotherStage;
	oldStage->Destroy();
}

ARaceStage* ARaceGameModeMOCK2::currentStage()
{
	return stage;
}

void ARaceGameModeMOCK2::addToRunningJets(AJet* aJet)
{
	runningJets.Add(aJet);
}

void ARaceGameModeMOCK2::createLapManagerMOCK()
{
	lapManager = GetWorld()->SpawnActor<ALapManagerMOCK>();
	lapManager->subscribeToLapCross(this);
}