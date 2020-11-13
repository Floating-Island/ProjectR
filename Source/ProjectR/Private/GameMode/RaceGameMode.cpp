// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/RaceGameMode.h"


#include "LapPhases/InitialLapPhase.h"
#include "Track/TrackGenerator.h"
#include "Jet/Jet.h"

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

	positionExpectedJets();
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
			distanceToTrackOrigin = track->length() - initialForwardDistanceBetweenJets;
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

void ARaceGameMode::createJet(FVector atLocation, int& aNumberOfremainingJetsToCreate)
{
	gameWorld->SpawnActor<AJet>(atLocation, FRotator(0));
	--aNumberOfremainingJetsToCreate;
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
