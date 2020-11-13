// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/RaceGameMode.h"


#include "LapPhases/InitialLapPhase.h"
#include "Track/TrackGenerator.h"
#include "Jet/Jet.h"

#include "Kismet/GameplayStatics.h"


ARaceGameMode::ARaceGameMode()
{
	numberOfPlayers = 1;
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
	float jetLength = AJet::length();
	while (numberOfJetsToCreate > 0)
	{
		distanceToTrackOrigin -= jetLength;
		if (distanceToTrackOrigin < 0)
		{
			distanceToTrackOrigin = track->length() - jetLength;
		}
		FVector segmentRightVector = track->rightVectorAt(distanceToTrackOrigin);
		FVector segmentLocation = track->locationAt(distanceToTrackOrigin);

		FVector jetLocation = segmentLocation + segmentRightVector * jetLength;
		createJet(jetLocation, numberOfJetsToCreate);
		if (numberOfJetsToCreate > 0)
		{
			jetLocation = segmentLocation - segmentRightVector * jetLength;
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
