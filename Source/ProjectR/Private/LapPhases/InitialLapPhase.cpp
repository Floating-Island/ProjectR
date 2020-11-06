// Fill out your copyright notice in the Description page of Project Settings.


#include "LapPhases/InitialLapPhase.h"
#include "LapPhases/IntermediateLapPhase.h"

ALapPhase* AInitialLapPhase::updatePhase(ALapPhase* anotherPhase)
{
	if(anotherPhase->GetClass() == AIntermediateLapPhase::StaticClass())
	{
		return anotherPhase;
	}
	else
	{
		return this;
	}
}
