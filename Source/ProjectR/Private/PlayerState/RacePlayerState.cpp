// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/RacePlayerState.h"

#include "PlayerController/ProjectRPlayerController.h"
#include "Net/UnrealNetwork.h"

void ARacePlayerState::fireLapUpdateEvent()
{
	lapUpdateEvent.Broadcast(lap);
}

void ARacePlayerState::firePositionUpdateEvent()
{
	positionUpdateEvent.Broadcast(position);
}

ARacePlayerState::ARacePlayerState()
{
	lap = 1;
	totalLapsValue = 0;
	position = 0;
	SetReplicates(true);
}

int ARacePlayerState::currentLap()
{
	return lap;
}

void ARacePlayerState::updateLapTo(int aCurrentLap)
{
	lap = aCurrentLap;
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
	lapUpdateEvent.AddUniqueDynamic(aRacePlayerUI, &URacePlayerUI::updateLapTo);
}

void ARacePlayerState::subscribeToPositionUpdate(URacePlayerUI* aRacePlayerUI)
{
	positionUpdateEvent.AddUniqueDynamic(aRacePlayerUI, &URacePlayerUI::updatePositionTo);
}

int ARacePlayerState::totalLaps()
{
	return totalLapsValue;
}

void ARacePlayerState::setTotalLapsTo(int aDesiredAmount)
{
	if(totalLapsValue == 0)
	{
		totalLapsValue = aDesiredAmount;
	}
}

UClass* ARacePlayerState::raceUIType()
{
	return raceUIClass;
}

void ARacePlayerState::fireEvents(APlayerController* controller)
{
	ARacePlayerState* self = Cast<ARacePlayerState, APlayerState>(controller->PlayerState);
	if(self == this)
	{
		fireLapUpdateEvent();
		firePositionUpdateEvent();
	}
}


void ARacePlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ARacePlayerState, lap);
}
