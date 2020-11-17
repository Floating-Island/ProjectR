// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/RaceGameMode.h"


#include "Jet/Jet.h"
#include "Track/TrackGenerator.h"
#include "LapPhases/InitialLapPhase.h"
#include "GameMode/RaceStages/RacePreparationStage.h"

#include "Kismet/GameplayStatics.h"



ARaceGameMode::ARaceGameMode()
{
	numberOfPlayers = 1;
	jetSpawnHeight = 100;
	initialForwardDistanceBetweenJets = 2000;
	initialLateralDistanceBetweenJets = 1000;
}

void ARaceGameMode::StartPlay()
{
	Super::StartPlay();
	
	gameWorld = GetWorld();
	AActor* soonToBeTrack = UGameplayStatics::GetActorOfClass(gameWorld, ATrackGenerator::StaticClass());
	track = Cast<ATrackGenerator, AActor>(soonToBeTrack);
	AActor* soonToBeInitialPhase = UGameplayStatics::GetActorOfClass(gameWorld, AInitialLapPhase::StaticClass());
	initialPhase = Cast<AInitialLapPhase, AActor>(soonToBeInitialPhase);

	stage = gameWorld->SpawnActor<ARacePreparationStage>();
	stage->start();
}

void ARaceGameMode::positionExpectedJets()
{
	int numberOfJetsToCreate = numberOfPlayers;
	float distanceToTrackOrigin = track->distanceAlongSplineOf(initialPhase);
	while (numberOfJetsToCreate > 0)
	{
		distanceToTrackOrigin -= initialForwardDistanceBetweenJets;
		if (distanceToTrackOrigin < 0)
		{
			distanceToTrackOrigin = track->length() + distanceToTrackOrigin;
		}
		FVector segmentRightVector = track->rightVectorAt(distanceToTrackOrigin);
		FVector segmentLocation = track->locationAt(distanceToTrackOrigin);
		FVector segmentUpVector = track->upVectorAt(distanceToTrackOrigin);

		FVector jetLocation = segmentLocation + segmentRightVector * initialLateralDistanceBetweenJets + segmentUpVector * jetSpawnHeight;
		createJet(jetLocation, numberOfJetsToCreate);
		if (numberOfJetsToCreate > 0)
		{
			jetLocation = segmentLocation - segmentRightVector * initialLateralDistanceBetweenJets + segmentUpVector * jetSpawnHeight;
			createJet(jetLocation, numberOfJetsToCreate);
		}
	}
}

void ARaceGameMode::createJet(FVector atLocation, int& aNumberOfRemainingJetsToCreate)
{
	AJet* spawnedJet = gameWorld->SpawnActor<AJet>(atLocation, FRotator(0));
	--aNumberOfRemainingJetsToCreate;
	runningJets.Add(spawnedJet);
}

int ARaceGameMode::jetsToSpawn()
{
	return numberOfPlayers;
}

TSet<AJet*> ARaceGameMode::jetsInPlay()
{
	return runningJets;
}

AInitialLapPhase* ARaceGameMode::initialLapPhase()
{
	return initialPhase;
}

void ARaceGameMode::updateStage(ARaceStage* broadcasterStage)
{
	if(broadcasterStage == stage)
	{
		ARaceStage* oldStage = stage;
		stage = stage->nextStage();
		stage->start();
		oldStage->Destroy();
	}
}
