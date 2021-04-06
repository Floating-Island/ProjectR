// Fill out your copyright notice in the Description page of Project Settings.


#include "LapManagerMOCK.h"


#include "Kismet/GameplayStatics.h"
#include "LapPhases/InitialLapPhase.h"
#include "LapPhases/IntermediateLapPhase.h"
#include "LapPhases/FinalLapPhase.h"

bool ALapManagerMOCK::defaultLapPhaseIsFinalLapPhase()
{
	AFinalLapPhase* FinalPhase = Cast<AFinalLapPhase, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AFinalLapPhase::StaticClass()));
	for (const auto& jet : jetsInPlay())
	{
		if (jet.Value.currentLapPhase != FinalPhase)
		{
			return false;
		}
	}
	return true;
}

bool ALapManagerMOCK::InitialLapCountSetToZero()
{
	for (const auto& jet : jetsInPlay())
	{
		if (jet.Value.lap != 0)
		{
			return false;
		}
	}
	return true;
}

bool ALapManagerMOCK::jetsMovedFromInitialToIntermediatePhase()
{
	for (const auto& jet : jetsInPlay())
	{
		if (jet.Value.currentLapPhase->GetClass() != AIntermediateLapPhase::StaticClass())
		{
			return false;
		}
	}
	return true;
}

void ALapManagerMOCK::makeJetsPhaseIntermediate()
{
	AIntermediateLapPhase* intermediatePhase = Cast<AIntermediateLapPhase, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AIntermediateLapPhase::StaticClass()));
	for (auto& jetLapData : jetLaps)
	{
		jetLapData.Value.currentLapPhase = intermediatePhase;
	}
}

bool ALapManagerMOCK::jetsMovedFromIntermediateToFinalPhase()
{
	for (const auto& jet : jetsInPlay())
	{
		if (jet.Value.currentLapPhase->GetClass() != AFinalLapPhase::StaticClass())
		{
			return false;
		}
	}
	return true;
}

void ALapManagerMOCK::makeJetsPhaseFinal()
{
	AFinalLapPhase* finalLapPhase = Cast<AFinalLapPhase, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AFinalLapPhase::StaticClass()));
	for (auto& jetLapData : jetLaps)
	{
		jetLapData.Value.currentLapPhase = finalLapPhase;
	}
}

bool ALapManagerMOCK::jetsMovedFromFinalToInitialPhase()
{
	for (const auto& jet : jetsInPlay())
	{
		if (jet.Value.currentLapPhase->GetClass() != AInitialLapPhase::StaticClass())
		{
			return false;
		}
	}
	return true;
}

void ALapManagerMOCK::changeLapTo(int aLapNumber, AJet* anAffectedJet)
{
	FLapData* oldJetData = jetLaps.Find(anAffectedJet);
	oldJetData->lap = aLapNumber;
}

void ALapManagerMOCK::makeJetsPhaseInitial()
{
	AInitialLapPhase* initialPhase = Cast<AInitialLapPhase, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AInitialLapPhase::StaticClass()));
	for (auto& jetLapData : jetLaps)
	{
		jetLapData.Value.currentLapPhase = initialPhase;
	}
}

bool ALapManagerMOCK::lastCrossedPhaseIs(UClass* aPhaseClass, AJet* anAffectedJet)
{
	for (auto& jetLapData : jetLaps)
	{
		if(jetLapData.Key == anAffectedJet && jetLapData.Value.lastCrossedPhase->GetClass() == aPhaseClass)
		{
			return true;
		}
	}
	return false;
}
