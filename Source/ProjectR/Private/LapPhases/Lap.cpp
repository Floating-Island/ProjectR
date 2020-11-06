// Fill out your copyright notice in the Description page of Project Settings.


#include "LapPhases/Lap.h"
#include "LapPhases/Phase1.h"

ALapPhase* ALap::updateState(ALapPhase* anotherPhase)
{
	if(anotherPhase->StaticClass() == APhase1::StaticClass())
	{
		return anotherPhase;
	}
	else
	{
		return this;
	}
}
