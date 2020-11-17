// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/RaceStages/RacePreparationStage.h"

#include "GameMode/RaceStages/RaceBeginningStage.h"
#include "GameMode/RaceGameMode.h"

void ARacePreparationStage::BeginPlay()
{
	Super::BeginPlay();
}

ARaceStage* ARacePreparationStage::nextStage()
{
	return GetWorld()->SpawnActor<ARaceBeginningStage>();
}

void ARacePreparationStage::start()
{
	raceMode->positionExpectedJets();
	stageEndedEvent.Broadcast(this);
}
