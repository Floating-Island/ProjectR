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
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
	initialLapPhase = Cast<AInitialLapPhase, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AInitialLapPhase::StaticClass()));
	AIntermediateLapPhase* intermediatePhase = Cast<AIntermediateLapPhase, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AIntermediateLapPhase::StaticClass()));
	AFinalLapPhase* finalPhase = Cast<AFinalLapPhase, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AFinalLapPhase::StaticClass()));

	checkPhaseAndSubscribe(initialLapPhase);
	checkPhaseAndSubscribe(intermediatePhase);
	checkPhaseAndSubscribe(finalPhase);
}

void ALapManager::checkPhaseAndSubscribe(ALapPhase* aPhase)
{
	if (aPhase)
	{
		aPhase->OnActorBeginOverlap.AddDynamic(this, &ALapManager::lapPhaseOverlap);
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
			if (initialLapPhase)
			{
				jetLapData.currentLapPhase = initialLapPhase;
			}
			jetLaps.Add(castedJet, jetLapData);
		}
	}
}

// Called every frame
void ALapManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	lapCompletedEvent.AddDynamic(aRaceMode, &ARaceGameMode::lapCompletedByJet);
}

