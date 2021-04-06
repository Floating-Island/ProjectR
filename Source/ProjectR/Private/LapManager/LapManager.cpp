// Fill out your copyright notice in the Description page of Project Settings.


#include "LapManager/LapManager.h"


#include "Jet/Jet.h"
#include "Kismet/GameplayStatics.h"
#include "LapPhases/LapPhase.h"
#include "LapPhases/InitialLapPhase.h"
#include "LapPhases/IntermediateLapPhase.h"
#include "LapPhases/FinalLapPhase.h"

// Sets default values
ALapManager::ALapManager()
{
	PrimaryActorTick.bCanEverTick = false;
	jetLaps = TMap<AJet*, FLapData>();
}


// Called when the game starts or when spawned
void ALapManager::BeginPlay()
{
	Super::BeginPlay();

	subscribeToLapPhases();

	configureJetLaps();
}

void ALapManager::subscribeToLapPhases()
{
	AInitialLapPhase* initialLapPhase = Cast<AInitialLapPhase, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AInitialLapPhase::StaticClass()));
	AIntermediateLapPhase* intermediatePhase = Cast<AIntermediateLapPhase, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AIntermediateLapPhase::StaticClass()));
	finalPhase = Cast<AFinalLapPhase, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AFinalLapPhase::StaticClass()));

	checkPhaseAndSubscribe(initialLapPhase);
	checkPhaseAndSubscribe(intermediatePhase);
	checkPhaseAndSubscribe(finalPhase);
}

void ALapManager::checkPhaseAndSubscribe(ALapPhase* aPhase)
{
	if (aPhase)
	{
		aPhase->OnActorBeginOverlap.AddUniqueDynamic(this, &ALapManager::lapPhaseOverlap);
	}
}

void ALapManager::configureJetLaps()
{
	TArray<AActor*> worldJets = TArray<AActor*>();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AJet::StaticClass(), worldJets);

	for (const auto& jet : worldJets)
	{
		AJet* castedJet = Cast<AJet, AActor>(jet);
		if (castedJet)
		{
			FLapData jetLapData = FLapData();
			if (finalPhase)
			{
				jetLapData.currentLapPhase = finalPhase;
			}
			jetLaps.Add(castedJet, jetLapData);
		}
	}
}

TMap<AJet*, FLapData> ALapManager::jetsInPlay()
{
	return jetLaps;
}

void ALapManager::lapPhaseOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	AJet* overlappedJet = Cast<AJet, AActor>(OtherActor);
	ALapPhase* overlappingPhase = Cast<ALapPhase, AActor>(OverlappedActor);
	if (overlappedJet && overlappingPhase)
	{
		FLapData* jetLapData = jetLaps.Find(overlappedJet);

		ALapPhase* oldPhase = jetLapData->currentLapPhase;
		jetLapData->currentLapPhase = jetLapData->currentLapPhase->updatePhase(overlappingPhase);
		ALapPhase* currentPhase = jetLapData->currentLapPhase;

		if (oldPhase->comesFromIntermediateLapPhase() && currentPhase->comesFromFinalLapPhase())
		{
			//oldPhase is then the final phase and the current phase is the initial phase.
			++jetLapData->lap;
			lapCompletedEvent.Broadcast(overlappedJet);
		}
	}
}

int ALapManager::currentLapOf(AJet* aJet)
{
	return jetLaps.Find(aJet)->lap;
}

void ALapManager::subscribeToLapCross(ARaceGameMode* aRaceMode)
{
	lapCompletedEvent.AddUniqueDynamic(aRaceMode, &ARaceGameMode::lapCompletedByJet);
}

