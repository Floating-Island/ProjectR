// Fill out your copyright notice in the Description page of Project Settings.


#include "LapPhases/IntermediateLapPhase.h"
#include "LapPhases/FinalLapPhase.h"


bool AIntermediateLapPhase::isNextPhase(ALapPhase* aPhase)
{
	return aPhase->GetClass() == AFinalLapPhase::StaticClass();
}
