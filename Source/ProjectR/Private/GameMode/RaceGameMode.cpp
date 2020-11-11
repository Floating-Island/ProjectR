// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/RaceGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Jet/Jet.h"

void ARaceGameMode::StartPlay()
{
	Super::StartPlay();
	TArray<AActor*> worldJets = TArray<AActor*>();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AJet::StaticClass(),worldJets);
	for(const auto& actor : worldJets)
	{
		AJet* jet = Cast<AJet,AActor>(actor);
		if(jet)
		{
			runningJets.Add(jet);
		}
	}
}

TSet<AJet*> ARaceGameMode::jetsInPlay()
{
	return runningJets;
}
