// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/RaceStages/RaceBeginningStage.h"

#include "TimerManager.h"
#include "PlayerController/ProjectRPlayerController.h"
#include "GameMode/RaceStages/RaceRunningStage.h"
#include "GameState/ProjectRGameState.h"


void ARaceBeginningStage::loadAnnouncerOnControllers()
{
	for (auto iterator = GetWorld()->GetPlayerControllerIterator(); iterator; ++iterator)
	{
		AProjectRPlayerController* controller = Cast<AProjectRPlayerController, APlayerController>(iterator->Get());
		controller->loadAnnouncerUI();
	}
}

void ARaceBeginningStage::start()
{
	loadAnnouncerOnControllers();
	FTimerDelegate countdownDelegate = FTimerDelegate::CreateUObject(this, &ARaceBeginningStage::countdownToStart, 3);
	GetWorldTimerManager().SetTimer(countdownTimer, countdownDelegate, 1, false, 1.0f);
}

void ARaceBeginningStage::countdownToStart(int countdown)
{
	AProjectRGameState* gameState = Cast<AProjectRGameState, AGameStateBase>(GetWorld()->GetGameState());
	if (countdown <= 0)
	{
		gameState->updateAnnouncerWith(FString("GO!"));
		stageEndedEvent.Broadcast(this);
		return;
	}
	gameState->updateAnnouncerWith(FString::FromInt(countdown));
	FTimerDelegate countdownDelegate = FTimerDelegate::CreateUObject(this, &ARaceBeginningStage::countdownToStart, --countdown);
	GetWorldTimerManager().SetTimer(countdownTimer, countdownDelegate, 1, false, 1.0f);
}

ARaceStage* ARaceBeginningStage::nextStage()
{
	return GetWorld()->SpawnActor<ARaceRunningStage>();
}