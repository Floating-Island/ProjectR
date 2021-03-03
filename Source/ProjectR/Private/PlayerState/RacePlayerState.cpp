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

void ARacePlayerState::fireTotalLapsSetEvent()
{
	totalLapsSetEvent.Broadcast(totalLapsValue);
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
	lapUpdateEvent.AddUniqueDynamic(aRacePlayerUI, &URacePlayerUI::updateLapTo);
}

void ARacePlayerState::subscribeToPositionUpdate(URacePlayerUI* aRacePlayerUI)
{
	positionUpdateEvent.AddUniqueDynamic(aRacePlayerUI, &URacePlayerUI::updatePositionTo);
}

void ARacePlayerState::subscribeToTotalLapsSet(URacePlayerUI* aRacePlayerUI)
{
	totalLapsSetEvent.AddUniqueDynamic(aRacePlayerUI, &URacePlayerUI::modifyTotalLapsTo);
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
		fireTotalLapsSetEvent();
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
		fireTotalLapsSetEvent();
	}
}


void ARacePlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ARacePlayerState, lap);
	DOREPLIFETIME(ARacePlayerState, position);
	DOREPLIFETIME(ARacePlayerState, totalLapsValue);
}
