// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceRunningStageMOCK.h"
#include "TimerManager.h"

bool ARaceRunningStageMOCK::announcerRemovalDelayStarted()
{
	return GetWorldTimerManager().IsTimerActive(announcerRemovalDelay) || GetWorldTimerManager().IsTimerPaused(announcerRemovalDelay) || GetWorldTimerManager().IsTimerPending(announcerRemovalDelay);
}
