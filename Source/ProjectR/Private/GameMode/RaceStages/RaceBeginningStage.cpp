// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/RaceStages/RaceBeginningStage.h"

#include "TimerManager.h"
#include "GameMode/RaceStages/RaceRunningStage.h"


void ARaceBeginningStage::start()
{
	FTimerDelegate countdownDelegate = FTimerDelegate::CreateUObject(this, &ARaceBeginningStage::countdownToStart, 3);
	GetWorldTimerManager().SetTimer(countdownTimer, countdownDelegate, 1, false, 1.0f);
}

void ARaceBeginningStage::countdownToStart(int countdown)
{
	if (countdown <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Announcer: GO!!!"));
		stageEndedEvent.Broadcast(this);
		return;
	}
	UE_LOG(LogTemp, Log, TEXT("Announcer: %d!"), countdown);
	FTimerDelegate countdownDelegate = FTimerDelegate::CreateUObject(this, &ARaceBeginningStage::countdownToStart, --countdown);
	GetWorldTimerManager().SetTimer(countdownTimer, countdownDelegate, 1, false, 1.0f);
}

ARaceStage* ARaceBeginningStage::nextStage()
{
	return GetWorld()->SpawnActor<ARaceRunningStage>();
}