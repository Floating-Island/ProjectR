// Fill out your copyright notice in the Description page of Project Settings.


#include "LapManager/LapManager.h"


#include "Jet/Jet.h"
#include "Kismet/GameplayStatics.h"
#include "LapPhases/LapPhase.h"
#include "LapPhases/InitialLapPhase.h"
#include "LapPhases/IntermediateLapPhase.h"

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

	AIntermediateLapPhase* intermediatePhase = Cast<AIntermediateLapPhase, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AIntermediateLapPhase::StaticClass()));
	intermediatePhase->subscribeToOverlap(this);

	configureJetLaps();
}

void ALapManager::configureJetLaps()
{
	initialPhase = Cast<AInitialLapPhase, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AInitialLapPhase::StaticClass()));

	TArray<AActor*> worldJets = TArray<AActor*>();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AJet::StaticClass(), worldJets);

	for (const auto& jet : worldJets)
	{
		AJet* castedJet = Cast<AJet, AActor>(jet);
		if (castedJet)
		{
			FLapData jetLapData = FLapData();
			if (initialPhase)
			{
				jetLapData.currentLapPhase = initialPhase;
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
		jetLapData->currentLapPhase = jetLapData->currentLapPhase->updatePhase(overlappingPhase);
	}
}

