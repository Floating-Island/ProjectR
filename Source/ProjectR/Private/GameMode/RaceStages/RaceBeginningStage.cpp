// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/RaceStages/RaceBeginningStage.h"
#include "TimerManager.h"

void ARaceBeginningStage::countdownToStart(int countdown)
{
	UE_LOG(LogTemp, Log, TEXT("Announcer: %d!"), countdown);
	FTimerDelegate countdownDelegate = FTimerDelegate::CreateUObject(this, &ARaceBeginningStage::countdownToStart, --countdown);
	GetWorldTimerManager().SetTimer(countdownTimer, countdownDelegate, 0, false, 1.0f);
}

void ARaceBeginningStage::start()
{
	FTimerDelegate countdownDelegate = FTimerDelegate::CreateUObject(this, &ARaceBeginningStage::countdownToStart, 3);
	GetWorldTimerManager().SetTimer(countdownTimer, countdownDelegate, 0, false, 1.0f);
}
