// Fill out your copyright notice in the Description page of Project Settings.


#include "LapPhases/IntermediateLapPhase.h"
#include "LapPhases/FinalLapPhase.h"

ALapPhase* AIntermediateLapPhase::updatePhase(ALapPhase* anotherPhase)
{
	if (anotherPhase->GetClass() == AFinalLapPhase::StaticClass())
	{
		return anotherPhase;
	}
	else
	{
		return this;
	}
}
