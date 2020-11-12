// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/RaceGameMode.h"
#include "Jet/Jet.h"


ARaceGameMode::ARaceGameMode()
{
	numberOfPlayers = 1;
}

void ARaceGameMode::StartPlay()
{
	Super::StartPlay();
	gameWorld = GetWorld();

	for (int jetsCreated = 0; jetsCreated < numberOfPlayers; ++jetsCreated)
	{
		AJet* newlyCreatedJet = gameWorld->SpawnActor<AJet>();
		runningJets.Add(newlyCreatedJet);
	}
}

int ARaceGameMode::jetsToSpawn()
{
	return numberOfPlayers;
}

TSet<AJet*> ARaceGameMode::jetsInPlay()
{
	return runningJets;
}
