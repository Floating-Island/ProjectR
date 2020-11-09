// Fill out your copyright notice in the Description page of Project Settings.


#include "LapPhases/InitialLapPhase.h"
#include "LapPhases/IntermediateLapPhase.h"


bool AInitialLapPhase::isNextPhase(ALapPhase* aPhase)
{
	return aPhase->GetClass() == AIntermediateLapPhase::StaticClass();
}
