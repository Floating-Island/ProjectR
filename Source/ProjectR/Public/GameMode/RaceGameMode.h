// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RaceGameMode.generated.h"

class AInitialLapPhase;
class ATrackGenerator;
class AJet;
/**
 *
 */
UCLASS()
class PROJECTR_API ARaceGameMode : public AGameModeBase
{
	GENERATED_BODY()

	TSet<AJet*> runningJets;
	UWorld* gameWorld;
	ATrackGenerator* track;
	AInitialLapPhase* initialPhase;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race Settings")
		int numberOfPlayers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race Settings")
		float jetSpawnHeight;

public:
	ARaceGameMode();
	
	void positionExpectedJets();
	void createJet(FVector atLocation, int& aNumberOfremainingJetsToCreate);

	void StartPlay() override;

	int jetsToSpawn();
	TSet<AJet*> jetsInPlay();

	AInitialLapPhase* initialLapPhase();
};
