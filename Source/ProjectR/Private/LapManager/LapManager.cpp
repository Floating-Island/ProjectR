// Fill out your copyright notice in the Description page of Project Settings.


#include "LapManager/LapManager.h"
#include "Jet/Jet.h"
#include "Kismet/GameplayStatics.h"
#include "LapPhases/LapPhase.h"
#include "LapPhases/InitialLapPhase.h"

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
	configureJetLaps();
}

void ALapManager::configureJetLaps()
{
	AInitialLapPhase* initialPhase = Cast<AInitialLapPhase, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AInitialLapPhase::StaticClass()));

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

