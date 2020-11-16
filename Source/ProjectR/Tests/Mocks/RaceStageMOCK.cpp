// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceStageMOCK.h"

bool ARaceStageMOCK::raceModeIsSubscribed()
{
	return stageEndedEvent.Contains(raceMode, &ARaceGameMode::StateUpate);
}
