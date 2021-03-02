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
	if (countdown <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("Announcer: GO!!!"));
		stageEndedEvent.Broadcast(this);
		return;
	}
	AProjectRGameState* gameState = Cast<AProjectRGameState, AGameStateBase>(GetWorld()->GetGameState());
	gameState->updateAnnouncerWith(FString::FromInt(countdown));
	FTimerDelegate countdownDelegate = FTimerDelegate::CreateUObject(this, &ARaceBeginningStage::countdownToStart, --countdown);
	GetWorldTimerManager().SetTimer(countdownTimer, countdownDelegate, 1, false, 1.0f);
}

ARaceStage* ARaceBeginningStage::nextStage()
{
	return GetWorld()->SpawnActor<ARaceRunningStage>();
}