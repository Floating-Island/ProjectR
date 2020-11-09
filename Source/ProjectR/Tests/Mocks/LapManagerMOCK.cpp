// Fill out your copyright notice in the Description page of Project Settings.


#include "LapManagerMOCK.h"
#include "Kismet/GameplayStatics.h"
#include "LapPhases/InitialLapPhase.h"

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
