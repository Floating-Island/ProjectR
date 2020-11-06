// Fill out your copyright notice in the Description page of Project Settings.


#include "LapPhases/InitialPhase.h"
#include "LapPhases/IntermediatePhase.h"

ALapPhase* AInitialPhase::updatePhase(ALapPhase* anotherPhase)
{
	if(anotherPhase->StaticClass() == AIntermediatePhase::StaticClass())
	{
		return anotherPhase;
	}
	else
	{
		return this;
	}
}
