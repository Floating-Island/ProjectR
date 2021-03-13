// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceBeginningStageMOCK.h"
#include "TimerManager.h"

bool ARaceBeginningStageMOCK::hasTimerActive()
{
	return GetWorldTimerManager().IsTimerActive(countdownTimer) || GetWorldTimerManager().IsTimerPaused(countdownTimer) || GetWorldTimerManager().IsTimerPending(countdownTimer);
}

void ARaceBeginningStageMOCK::loadAnnouncers()
{
	loadAnnouncerOnControllers();
}
