// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceStageMOCK.h"
#include "GameMode/RaceGameMode.h"

bool ARaceStageMOCK::raceModeIsSubscribed()
{
	return stageEndedEvent.Contains(raceMode, FName("stageUpdate"));
}
