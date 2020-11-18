// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/RaceGameMode.h"



#include "LapManager/LapManager.h"
#include "Jet/Jet.h"
#include "Track/TrackGenerator.h"
#include "LapPhases/InitialLapPhase.h"
#include "GameMode/RaceStages/RacePreparationStage.h"

#include "Kismet/GameplayStatics.h"



ARaceGameMode::ARaceGameMode()
{
	numberOfPlayers = 1;
	numberOfLaps = 3;
	jetSpawnHeight = 100;
	initialForwardDistanceBetweenJets = 2000;
	initialLateralDistanceBetweenJets = 1000;

	currentJetPositions = TMap<AJet*, int8>();
	finalizedJets = TArray<AJet*>();
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

TSet<AJet*> ARaceGameMode::jetsRacing()
{
	return runningJets;
}

AInitialLapPhase* ARaceGameMode::initialLapPhase()
{
	return initialPhase;
}

void ARaceGameMode::updateStage(ARaceStage* broadcasterStage)
{
	if (broadcasterStage == stage)
	{
		ARaceStage* oldStage = stage;
		stage = stage->nextStage();
		stage->start();
		oldStage->Destroy();
	}
}

TMap<AJet*, int8> ARaceGameMode::calculateJetPositions()
{
	TMap<AJet*, float> scoredPositions = TMap<AJet*, float>();

	for (auto& jet : runningJets)
	{
		float scoredPosition = track->distanceAlongSplineOf(jet) + lapManager->currentLapOf(jet) * track->length();
		scoredPositions.Add(jet, scoredPosition);
	}

	scoredPositions.ValueSort([](float ahead, float behind) {return ahead > behind; });//biggest value = jet ahead of the rest.

	TArray<AJet*> orderedJets = TArray<AJet*>();
	scoredPositions.GenerateKeyArray(orderedJets);

	TMap<AJet*, int8> positions = TMap<AJet*, int8>();
	int8 position = 1;
	for (auto& jet : finalizedJets)
	{
		positions.Add(jet, position);
		++position;
	}
	for (auto& jet : orderedJets)
	{
		positions.Add(jet, position);
		++position;
	}
	return positions;
}

void ARaceGameMode::createLapManager()
{
	lapManager = GetWorld()->SpawnActor<ALapManager>();
	lapManager->subscribeToLapCross(this);
}

void ARaceGameMode::updateJetPositions()
{
	currentJetPositions = calculateJetPositions();
}

int ARaceGameMode::laps()
{
	return numberOfLaps;
}

void ARaceGameMode::lapCompletedByJet(AJet* aCrossingJet)
{
	if(runningJets.Contains(aCrossingJet))
	{
		if(lapManager->currentLapOf(aCrossingJet) > laps())
		{
			runningJets.Remove(aCrossingJet);
			finalizedJets.Add(aCrossingJet);
			UE_LOG(LogTemp, Log, TEXT("A Jet has finished laps!!!"));
		}
	}
}

TArray<AJet*> ARaceGameMode::finalistJets()
{
	return finalizedJets;
}
