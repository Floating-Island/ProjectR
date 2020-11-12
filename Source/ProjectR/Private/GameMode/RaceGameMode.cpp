// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/RaceGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Jet/Jet.h"

void ARaceGameMode::actorReadyToStore(const FActorsInitializedParams& parameters)
{
	
}

ARaceGameMode::ARaceGameMode()
{
	
}

void ARaceGameMode::StartPlay()
{
	Super::StartPlay();
	//let's create some jets

}

int ARaceGameMode::jetsToSpawn()
{
	return numberOfPlayers;
}

TSet<AJet*> ARaceGameMode::jetsInPlay()
{
	return runningJets;
}
