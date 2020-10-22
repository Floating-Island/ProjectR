// Fill out your copyright notice in the Description page of Project Settings.


#include "Track/TrackManager.h"

#include "Jet/Jet.h"
#include "Track/TrackGenerator.h"
#include "Kismet/GameplayStatics.h"


ATrackManager::ATrackManager()
{
	PrimaryActorTick.bCanEverTick = true;
	jetsToMagnetize = TSet<AJet*>();//should do the same with the track generator set.
}

void ATrackManager::BeginPlay()
{
	Super::BeginPlay();
	collectTrackGenerators();
	for(auto generator : trackGeneratorSet)
	{
		generator->toMagnetOverlapSubscribe(this);
	}
}

void ATrackManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ATrackManager::collectTrackGenerators()
{
	TArray<AActor*> spawnedGenerators = TArray<AActor*>();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATrackGenerator::StaticClass(), spawnedGenerators);
	for (auto generator : spawnedGenerators)
	{
		ATrackGenerator* trackGenerator = Cast<ATrackGenerator, AActor>(generator);
		if (trackGenerator)
		{
			trackGeneratorSet.Add(trackGenerator);
		}
	}
}

void ATrackManager::addJetToMagnetize(UPrimitiveComponent* OverlappedComponent,
										AActor* OtherActor,
										UPrimitiveComponent* OtherComp,
										int32 OtherBodyIndex,
										bool bFromSweep,
										const FHitResult& SweepResult)
{
	AJet* overlappedJet = Cast<AJet, AActor>(OtherActor);
	if(overlappedJet)
	{
		jetsToMagnetize.Add(overlappedJet);	
	}
}