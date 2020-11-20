// Fill out your copyright notice in the Description page of Project Settings.


#include "LapPhases/InitialLapPhase.h"
#include "LapPhases/IntermediateLapPhase.h"


bool AInitialLapPhase::nextPhaseIs(ALapPhase* aPhase)
{
	return aPhase->comesFromInitialLapPhase();
}

bool AInitialLapPhase::comesFromFinalLapPhase()
{
	return true;
}

