// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/RacePlayerState.h"

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
}

int ARacePlayerState::currentPosition()
{
	return position;
}

void ARacePlayerState::updatePositionTo(int aCurrentPosition)
{
	position = aCurrentPosition;
}
