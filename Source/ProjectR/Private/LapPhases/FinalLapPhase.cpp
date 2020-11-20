// Fill out your copyright notice in the Description page of Project Settings.


#include "LapPhases/FinalLapPhase.h"
#include "LapPhases/InitialLapPhase.h"


bool AFinalLapPhase::nextPhaseIs(ALapPhase* aPhase)
{
	return aPhase->comesFromFinalLapPhase();
}

bool AFinalLapPhase::comesFromIntermediateLapPhase()
{
	return true;
}
