// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "../LapPhases/FinalLapPhase.h"
#include "GameFramework/Actor.h"
#include "LapManager.generated.h"


class ARaceGameMode;
class AJet;
class ALapPhase;
class AInitialLapPhase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLapCrossedEvent, AJet*, aCrossingJet);

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
	AInitialLapPhase* initialLapPhase;

public:
	// Sets default values for this actor's properties
	ALapManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TMap<AJet*, FLapData> jetLaps;
	void configureJetLaps();
	void subscribeToLapPhases();
	void checkPhaseAndSubscribe(ALapPhase* aPhase);

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FLapCrossedEvent lapCrossedEvent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TMap<AJet*, FLapData> jetsInPlay();

	UFUNCTION()
		void lapPhaseOverlap(AActor* OverlappedActor, AActor* OtherActor);

	int currentLapOf(AJet* aJet);

	void subscribeToLapCross(ARaceGameMode* aRaceMode);
};
