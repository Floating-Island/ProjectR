// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/RaceStages/RacePreparationStage.h"

#include "GameMode/RaceStages/RaceBeginningStage.h"

ARaceStage* ARacePreparationStage::nextStage()
{
	return GetWorld()->SpawnActor<ARaceBeginningStage>();
}
