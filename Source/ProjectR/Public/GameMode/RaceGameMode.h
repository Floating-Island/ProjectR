// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RaceGameMode.generated.h"

class ARaceStage;
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

	

protected:

	TSet<AJet*> runningJets;
	UWorld* gameWorld;
	ATrackGenerator* track;
	AInitialLapPhase* initialPhase;
	ARaceStage* stage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race Settings")
		int numberOfPlayers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race Settings")
		float jetSpawnHeight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race Settings")
		float initialLateralDistanceBetweenJets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race Settings")
		float initialForwardDistanceBetweenJets;

public:
	ARaceGameMode();
	
	void positionExpectedJets();
	void createJet(FVector atLocation, int& aNumberOfRemainingJetsToCreate);

	virtual void StartPlay() override;

	int jetsToSpawn();
	TSet<AJet*> jetsInPlay();

	AInitialLapPhase* initialLapPhase();

	UFUNCTION()
		void stageUpdate(ARaceStage* broadcasterStage);
};
