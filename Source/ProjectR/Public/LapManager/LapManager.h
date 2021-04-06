// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "GameFramework/Actor.h"
#include "LapManager.generated.h"


class ARaceGameMode;
class AJet;
class ALapPhase;
class AFinalLapPhase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLapCompletedEvent, AJet*, aCrossingJet);

USTRUCT()
struct FLapData
{
	GENERATED_BODY()

	int lap = 0;
	ALapPhase* currentLapPhase;
};

UCLASS()
class PROJECTR_API ALapManager : public AActor
{
	GENERATED_BODY()

private:
	AFinalLapPhase* finalPhase;

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
		FLapCompletedEvent lapCompletedEvent;

public:

	TMap<AJet*, FLapData> jetsInPlay();

	UFUNCTION()
		void lapPhaseOverlap(AActor* OverlappedActor, AActor* OtherActor);

	int currentLapOf(AJet* aJet);

	void subscribeToLapCross(ARaceGameMode* aRaceMode);
};
