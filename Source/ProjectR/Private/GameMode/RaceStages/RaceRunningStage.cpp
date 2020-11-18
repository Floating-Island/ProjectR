// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/RaceStages/RaceRunningStage.h"

#include "GameMode/RaceStages/RaceEndedStage.h"

ARaceStage* ARaceRunningStage::nextStage()
{
	return GetWorld()->SpawnActor<ARaceEndedStage>();
}

void ARaceRunningStage::start()
{
	raceMode->createLapManager();
}
