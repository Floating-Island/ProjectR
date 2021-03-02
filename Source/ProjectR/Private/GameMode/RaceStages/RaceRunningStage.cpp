// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/RaceStages/RaceRunningStage.h"


#include "PlayerController/ProjectRPlayerController.h"
#include "GameMode/RaceStages/RaceEndedStage.h"
#include "GameMode/RaceGameMode.h"

void ARaceRunningStage::removeAnnouncersFromControllers()
{
	for (auto iterator = GetWorld()->GetPlayerControllerIterator(); iterator; ++iterator)
	{
		AProjectRPlayerController* controller = Cast<AProjectRPlayerController, APlayerController>(iterator->Get());
		if(controller)
		{
			controller->removeAnnouncerUI();
		}
	}
}

ARaceStage* ARaceRunningStage::nextStage()
{
	return GetWorld()->SpawnActor<ARaceEndedStage>();
}

void ARaceRunningStage::Tick(float DeltaSeconds)
{
	Super::Super::Tick(DeltaSeconds);
	raceMode->updateJetPositions();
	if (raceMode->jetsRacing().Num() == 0)
	{
		stageEndedEvent.Broadcast(this);
	}
}

void ARaceRunningStage::start()
{
	FTimerDelegate removalDelegate = FTimerDelegate::CreateUObject(this, &ARaceRunningStage::removeAnnouncersFromControllers);
	GetWorldTimerManager().SetTimer(announcerRemovalDelay, removalDelegate, 2.5f, false, 1.0f);
	raceMode->enableJetsInput();
}
