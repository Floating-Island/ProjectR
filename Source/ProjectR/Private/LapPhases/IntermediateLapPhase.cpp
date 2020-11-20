// Fill out your copyright notice in the Description page of Project Settings.


#include "LapPhases/IntermediateLapPhase.h"
#include "LapPhases/FinalLapPhase.h"


bool AIntermediateLapPhase::nextPhaseIs(ALapPhase* aPhase)
{
	return aPhase->comesFromIntermediateLapPhase();
}

bool AIntermediateLapPhase::comesFromInitialLapPhase()
{
	return true;
}
