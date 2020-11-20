// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/RaceStages/RaceRunningStage.h"

#include "GameMode/RaceStages/RaceEndedStage.h"
#include "GameMode/RaceGameMode.h"

ARaceStage* ARaceRunningStage::nextStage()
{
	return GetWorld()->SpawnActor<ARaceEndedStage>();
}

void ARaceRunningStage::Tick(float DeltaSeconds)
{
	Super::Super::Tick(DeltaSeconds);
	raceMode->updateJetPositions();
	if (raceMode->jetsRacing().Num() == 0)
	{
		stageEndedEvent.Broadcast(this);
	}
}
