// Fill out your copyright notice in the Description page of Project Settings.


#include "LapPhases/FinalLapPhase.h"
#include "LapPhases/InitialLapPhase.h"


bool AFinalLapPhase::isNextPhase(ALapPhase* aPhase)
{
	return aPhase->GetClass() == AInitialLapPhase::StaticClass();
}
