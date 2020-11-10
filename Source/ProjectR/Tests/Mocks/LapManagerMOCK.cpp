// Fill out your copyright notice in the Description page of Project Settings.


#include "LapManagerMOCK.h"


#include "Kismet/GameplayStatics.h"
#include "LapPhases/InitialLapPhase.h"
#include "LapPhases/IntermediateLapPhase.h"
#include "LapPhases/FinalLapPhase.h"

bool ALapManagerMOCK::defaultLapPhaseIsInitialLapPhase()
{
	AInitialLapPhase* initialPhase = Cast<AInitialLapPhase, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(),AInitialLapPhase::StaticClass()));
	for(const auto& jet : jetsInPlay())
	{
		if(jet.Value.currentLapPhase != initialPhase)
		{
			return false;
		}
	}
	return true;
}

bool ALapManagerMOCK::InitialLapCountSetToOne()
{
	for(const auto& jet : jetsInPlay())
	{
		if(jet.Value.lap != 1)
		{
			return false;
		}
	}
	return true;
}

bool ALapManagerMOCK::jetsMovedFromInitialToIntermediatePhase()
{
	for(const auto& jet : jetsInPlay())
	{
		if(jet.Value.currentLapPhase->GetClass() != AIntermediateLapPhase::StaticClass())
		{
			return false;
		}
	}
	return true;
}

void ALapManagerMOCK::makeJetsPhaseIntermediate()
{
	AIntermediateLapPhase* intermediatePhase = Cast<AIntermediateLapPhase, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(),AIntermediateLapPhase::StaticClass()));
	for(auto& jetLapData : jetLaps)
	{
		jetLapData.Value.currentLapPhase = intermediatePhase;
	}
}

bool ALapManagerMOCK::jetsMovedFromIntermediateToFinalPhase()
{
	for(const auto& jet : jetsInPlay())
	{
		if(jet.Value.currentLapPhase->GetClass() != AFinalLapPhase::StaticClass())
		{
			return false;
		}
	}
	return true;
}
