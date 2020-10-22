// Fill out your copyright notice in the Description page of Project Settings.


#include "Track/TrackManager.h"

#include "Jet/Jet.h"
#include "Track/TrackGenerator.h"
#include "Kismet/GameplayStatics.h"


ATrackManager::ATrackManager()
{
	PrimaryActorTick.bCanEverTick = true;
	trackGeneratorSet = TSet<ATrackGenerator*>();
	jetsToMagnetize = TMap<AJet*,ATrackGenerator*>();
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
	for (auto jetTrackGeneratorPair : jetsToMagnetize)
	{
		AJet* jet = jetTrackGeneratorPair.Key;
		ATrackGenerator* trackGenerator = jetTrackGeneratorPair.Value;

		FVector jetLocation = jet->GetActorLocation();
		FVector generatorLocation = trackGenerator->closestLocationTo(jetLocation);

		FHitResult hit;
		FCollisionQueryParams collisionParameters;
		collisionParameters.AddIgnoredActor(jet);
		collisionParameters.bTraceComplex = false;
		
		bool hitBlocked = GetWorld()->LineTraceSingleByChannel(hit, jetLocation, generatorLocation, ECollisionChannel::ECC_WorldStatic, collisionParameters);
		
		if(hitBlocked)
		{
			FVector roadNormal = hit.ImpactNormal;
			UStaticMeshComponent* jetRoot = Cast<UStaticMeshComponent, USceneComponent>(jet->GetRootComponent());
			
			if (jetRoot && jetRoot->IsSimulatingPhysics())
			{
				FVector gravityAccelerationAbsolute = jet->GetGravityDirection() * GetWorld()->GetGravityZ();
				FVector jetWeightAbsolute = gravityAccelerationAbsolute * jetRoot->GetMass();
				magnetize(jetRoot, jetWeightAbsolute, roadNormal);
			}
		}
	}
}

void ATrackManager::magnetize(UStaticMeshComponent* aJetRootComponent, FVector aJetWeightAbsolute, FVector aRoadNormal)
{
	CounterGravityForce(aJetRootComponent, aJetWeightAbsolute);
	pullTowardsFloor(aJetRootComponent, aJetWeightAbsolute, aRoadNormal);
}

void ATrackManager::CounterGravityForce(UStaticMeshComponent* aJetRootComponent, FVector aJetWeightAbsolute)
{
	aJetRootComponent->AddForce(aJetWeightAbsolute);//counter the weight force....
}

void ATrackManager::pullTowardsFloor(UStaticMeshComponent* aJetRootComponent, FVector aJetWeightAbsolute, FVector aRoadNormal)
{
	FVector magnet = -aRoadNormal * aJetWeightAbsolute.Size();//notice the '-' it needs to pull, so the normal has to be inverted.
	aJetRootComponent->AddForce(magnet);
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
	ATrackGenerator* generator = Cast<ATrackGenerator,AActor>(OverlappedComponent->GetOwner());
	if(overlappedJet && generator)
	{
		jetsToMagnetize.Add(overlappedJet, generator);
	}
}