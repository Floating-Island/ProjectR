// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "LapManager.generated.h"


class AJet;
class ALapPhase;

USTRUCT()
struct FLapData
{
	GENERATED_BODY()

	int lap = 1;
	ALapPhase* currentLapPhase;
};

UCLASS()
class PROJECTR_API ALapManager : public AActor
{
	GENERATED_BODY()

private:
	TMap<AJet*, FLapData> jetLaps;

public:
	// Sets default values for this actor's properties
	ALapManager();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void configureJetLaps();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TMap<AJet*, FLapData> jetsInPlay();

};
