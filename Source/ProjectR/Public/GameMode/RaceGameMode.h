// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RaceGameMode.generated.h"

class ALapManager;
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
	ALapManager* lapManager;
	TMap<AJet*, int8> currentJetPositions;
	TArray<AJet*> finalizedJets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race Settings")
		int numberOfLaps;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race Settings")
		float jetSpawnHeight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race Settings")
		float initialLateralDistanceBetweenJets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race Settings")
		float initialForwardDistanceBetweenJets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Race Settings")
		TSubclassOf<AJet> jetClass;

public:
	ARaceGameMode();

	void positionExpectedJets();
	void createJet(FVector atLocation, FRotator atRotation, int& aNumberOfRemainingJetsToCreate);

	virtual void StartPlay() override;

	int jetsToSpawn();
	TSet<AJet*> jetsRacing();

	AInitialLapPhase* initialLapPhase();

	UFUNCTION()
		void updateStage(ARaceStage* broadcasterStage);

	TMap<AJet*, int8> calculateJetPositions();

	void createLapManager();

	void updateJetPositions();

	int laps();

	UFUNCTION()
		void lapCompletedByJet(AJet* aCrossingJet);

	TArray<AJet*> finalistJets();

	TMap<AJet*, int8> positions();

	void playersToCreate(int aPlayerQuantity);

	void achieveNecessaryPlayersQuantity();

	void possessJets();

	void disableJetsInput();
	void enableJetsInput();
	

};
