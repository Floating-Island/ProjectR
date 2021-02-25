// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/RacePlayerState.h"

#include "PlayerController/ProjectRPlayerController.h"

void ARacePlayerState::fireLapUpdateEvent()
{
	lapUpdateEvent.Broadcast(lap);
}

void ARacePlayerState::firePositionUpdateEvent()
{
	positionUpdateEvent.Broadcast(position);
}

void ARacePlayerState::showRaceUI()
{
	raceUI->AddToViewport();
}

ARacePlayerState::ARacePlayerState()
{
	lap = 0;
	position = 0;
}

int ARacePlayerState::currentLap()
{
	return lap;
}

void ARacePlayerState::updateLapTo(int aCurrentLap)
{
	lap = aCurrentLap;
	fireLapUpdateEvent();
}

int ARacePlayerState::currentPosition()
{
	return position;
}

void ARacePlayerState::updatePositionTo(int aCurrentPosition)
{
	position = aCurrentPosition;
	firePositionUpdateEvent();
}

void ARacePlayerState::subscribeToLapUpdate(URacePlayerUI* aRacePlayerUI)
{
	lapUpdateEvent.AddDynamic(aRacePlayerUI, &URacePlayerUI::updateLapTo);
}

void ARacePlayerState::subscribeToPositionUpdate(URacePlayerUI* aRacePlayerUI)
{
	positionUpdateEvent.AddDynamic(aRacePlayerUI, &URacePlayerUI::updatePositionTo);
}

void ARacePlayerState::loadRaceUI(APlayerController* playerController)
{
	if(raceUIClass)
	{
		if (!raceUI || raceUI->IsUnreachable())
		{
			raceUI = CreateWidget<URacePlayerUI>(playerController->GetWorld(), raceUIClass, FName("Race UI"));
		}
		if (!raceUI->IsInViewport())
		{
			showRaceUI();
		}
	}
}
