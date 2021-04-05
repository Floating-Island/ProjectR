// Fill out your copyright notice in the Description page of Project Settings.


#include "Track/TrackManager.h"

#include "Jet/Jet.h"
#include "Track/TrackGenerator.h"
#include "Kismet/GameplayStatics.h"


ATrackManager::ATrackManager()
{
	PrimaryActorTick.bCanEverTick = true;
	trackGeneratorSet = TSet<ATrackGenerator*>();
	jetsToMagnetize = TMap<AJet*, ATrackGenerator*>();
}



void ATrackManager::BeginPlay()
{
	Super::BeginPlay();
	collectTrackGenerators();
	subscribeToTrackGeneratorsMagnetSplines();
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

void ATrackManager::subscribeToTrackGeneratorsMagnetSplines()
{
	for (auto generator : trackGeneratorSet)
	{
		generator->toMagnetOverlapSubscribe(this);
	}
}


void ATrackManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	manageMagnetization();
}

void ATrackManager::manageMagnetization()
{
	for (auto jetTrackGeneratorPair : jetsToMagnetize)
	{
		AJet* jet = jetTrackGeneratorPair.Key;
		ATrackGenerator* trackGenerator = jetTrackGeneratorPair.Value;

		FVector jetLocation = jet->GetActorLocation();
		FVector generatorLocation = trackGenerator->closestLocationTo(jetLocation);
		FHitResult hit;
		FCollisionQueryParams collisionParameters;
		collisionParameters.AddIgnoredActor(jet);
		collisionParameters.bTraceComplex = true;
		int directionMultiplier = 2;
		FVector traceEnd = (generatorLocation - jetLocation) * directionMultiplier + jetLocation;//get the direction of the trace, make it double and set it at the jet location.

		bool hitBlocked = GetWorld()->LineTraceSingleByChannel(hit, jetLocation, traceEnd, ECollisionChannel::ECC_Visibility, collisionParameters);

		prepareMagnetization(jet, hit, hitBlocked);
	}
}

void ATrackManager::prepareMagnetization(AJet* aJet, FHitResult aHit, bool wasHitBlocked)
{
	if (wasHitBlocked)
	{
		FVector roadNormal = aHit.Component->GetUpVector();//could be a problem if the spline has roll... Change it to hit impact normal when it's needed.

		UStaticMeshComponent* jetRoot = Cast<UStaticMeshComponent, USceneComponent>(aJet->GetRootComponent());

		if (jetRoot && jetRoot->IsSimulatingPhysics())
		{
			FVector gravityAccelerationAbsolute = aJet->GetGravityDirection() * GetWorld()->GetGravityZ();
			FVector jetWeightAbsolute = gravityAccelerationAbsolute * jetRoot->GetMass();
			magnetize(jetRoot, jetWeightAbsolute, roadNormal);
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

void ATrackManager::addJetToMagnetize(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	AJet* overlappedJet = Cast<AJet, AActor>(OtherActor);
	ATrackGenerator* generator = Cast<ATrackGenerator, AActor>(OverlappedComponent->GetOwner());
	if (overlappedJet && generator)
	{
		jetsToMagnetize.Add(overlappedJet, generator);
	}
}

bool ATrackManager::hasJetsStored()
{
	return jetsToMagnetize.Num() > 0 ? true : false;
}

void ATrackManager::addGeneratorAndSubscribe(ATrackGenerator* newGenerator)
{
	trackGeneratorSet.Add(newGenerator);
	newGenerator->toMagnetOverlapSubscribe(this);
}

FVector ATrackManager::pullingAccelerationTo(AJet* aJet)
{
	ATrackGenerator* const trackGenerator = *jetsToMagnetize.Find(aJet);

	FVector jetLocation = aJet->GetActorLocation();
	FVector generatorLocation = trackGenerator->closestLocationTo(jetLocation);
	FHitResult hit;
	FCollisionQueryParams collisionParameters;
	collisionParameters.AddIgnoredActor(aJet);
	collisionParameters.bTraceComplex = true;
	int directionMultiplier = 2;
	FVector traceEnd = (generatorLocation - jetLocation) * directionMultiplier + jetLocation;//get the direction of the trace, make it double and set it at the jet location.

	bool hitBlocked = GetWorld()->LineTraceSingleByChannel(hit, jetLocation, traceEnd, ECollisionChannel::ECC_Visibility, collisionParameters);

	FVector magnetPullingAcceleration = FVector(0, 0, GetWorld()->GetGravityZ());
	if (hitBlocked)
	{
		FVector roadNormal = hit.Component->GetUpVector();//could be a problem if the spline has roll... Change it to hit impact normal when it's needed.
		magnetPullingAcceleration = roadNormal * GetWorld()->GetGravityZ();//gravity Z is already negative, roadNormal points 'up'
	}
	
	return magnetPullingAcceleration;
}
