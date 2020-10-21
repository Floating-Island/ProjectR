// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Track/TrackGenerator.h"
#include "TrackManager.generated.h"

UCLASS()
class PROJECTR_API ATrackManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrackManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ATrackGenerator* trackGenerator;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
};

inline void ATrackManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	trackGenerator = GetWorld()->SpawnActor<ATrackGenerator>(ATrackGenerator::StaticClass());
}
