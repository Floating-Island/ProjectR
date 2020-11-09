// Fill out your copyright notice in the Description page of Project Settings.


#include "LapManager/LapManager.h"
#include "Jet/Jet.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALapManager::ALapManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	jetLaps = TSet<AJet*>();
}

// Called when the game starts or when spawned
void ALapManager::BeginPlay()
{
	Super::BeginPlay();
	storeJetsFromWorld();
}

void ALapManager::storeJetsFromWorld()
{
	TArray<AActor*> worldJets = TArray<AActor*>();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AJet::StaticClass(),worldJets);
	for (const auto& jet: worldJets)
	{
		AJet* castedJet = Cast<AJet,AActor>(jet);
		if(castedJet)
		{
			jetLaps.Add(castedJet);
		}
	}
}

// Called every frame
void ALapManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TSet<AJet*> ALapManager::jetsInPlay()
{
	return jetLaps;
}

