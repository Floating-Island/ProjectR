// Fill out your copyright notice in the Description page of Project Settings.


#include "LapPhases/FinalLapPhase.h"
#include "LapPhases/InitialLapPhase.h"

ALapPhase* AFinalLapPhase::updatePhase(ALapPhase* anotherPhase)
{
	if (anotherPhase->GetClass() == AInitialLapPhase::StaticClass())
	{
		return anotherPhase;
	}
	else
	{
		return this;
	}
}
