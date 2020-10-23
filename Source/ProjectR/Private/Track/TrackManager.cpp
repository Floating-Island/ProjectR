// Fill out your copyright notice in the Description page of Project Settings.


#include "Track/TrackManager.h"

#include "Jet/Jet.h"
#include "Track/TrackGenerator.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


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
	for (auto generator : trackGeneratorSet)
	{
		UE_LOG(LogTemp, Log, TEXT("subscribing to components."));
		generator->toMagnetOverlapSubscribe(this);
	}
}

void ATrackManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Log, TEXT("ticking."));
	for (auto jetTrackGeneratorPair : jetsToMagnetize)
	{
		AJet* jet = jetTrackGeneratorPair.Key;
		ATrackGenerator* trackGenerator = jetTrackGeneratorPair.Value;

		FVector jetLocation = jet->GetActorLocation();
		FVector generatorLocation = trackGenerator->closestLocationTo(jetLocation);
		UE_LOG(LogTemp, Log, TEXT("jet location: %s."), *jetLocation.ToString());
		UE_LOG(LogTemp, Log, TEXT("closest track generator point to jet: %s."), *generatorLocation.ToString());
		FHitResult hit;
		FCollisionQueryParams collisionParameters;
		collisionParameters.AddIgnoredActor(jet);
		collisionParameters.bTraceComplex = true;
		int directionMultiplier = 2;
		FVector traceEnd = (generatorLocation - jetLocation) * directionMultiplier + jetLocation;//get the direction of the trace, make it double and set it at the jet location.
		bool hitBlocked = GetWorld()->LineTraceSingleByChannel(hit, jetLocation, traceEnd, ECollisionChannel::ECC_Visibility, collisionParameters);
		DrawDebugLine(GetWorld(), jetLocation, traceEnd, FColor::Red, false, 0.5f, 0, 5);
		//DrawDebugLine(GetWorld(), jetLocation, generatorLocation, FColor::Blue, false, 0.5f, 0, 5);
		if (hitBlocked)
		{
			UE_LOG(LogTemp, Log, TEXT("hitted something."));
			FVector roadNormal = hit.Component->GetUpVector();//could be a problem if the spline has roll...

			UStaticMeshComponent* jetRoot = Cast<UStaticMeshComponent, USceneComponent>(jet->GetRootComponent());

			if (jetRoot && jetRoot->IsSimulatingPhysics())
			{
				UE_LOG(LogTemp, Log, TEXT("the jet root."));
				UE_LOG(LogTemp, Log, TEXT("Road Normal: %s."), *roadNormal.ToString());
				FVector gravityAccelerationAbsolute = jet->GetGravityDirection() * GetWorld()->GetGravityZ();
				UE_LOG(LogTemp, Log, TEXT("Gravity acceleration: %s."), *gravityAccelerationAbsolute.ToString());
				FVector jetWeightAbsolute = gravityAccelerationAbsolute * jetRoot->GetMass();
				UE_LOG(LogTemp, Log, TEXT("Jet weight absolute: %s."), *jetWeightAbsolute.ToString());
				magnetize(jetRoot, jetWeightAbsolute, roadNormal);
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("no hit."));
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
		UE_LOG(LogTemp, Log, TEXT("got a track generator."));
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
	ATrackGenerator* generator = Cast<ATrackGenerator, AActor>(OverlappedComponent->GetOwner());
	UE_LOG(LogTemp, Log, TEXT("overlapped with something."));
	UE_LOG(LogTemp, Log, TEXT("the other actor %s a jet."), *FString(overlappedJet ? "is" : "isn't"));
	UE_LOG(LogTemp, Log, TEXT("the other component's owner %s a track generator."), *FString(generator ? "is" : "isn't"));
	if (overlappedJet && generator)
	{
		jetsToMagnetize.Add(overlappedJet, generator);
		UE_LOG(LogTemp, Log, TEXT("added overlapped jet and generator to map."));
	}
}