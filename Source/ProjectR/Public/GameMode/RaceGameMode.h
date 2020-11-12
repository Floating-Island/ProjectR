// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RaceGameMode.generated.h"

class AJet;
class FActorsInitializedParams;
/**
 * 
 */
UCLASS()
class PROJECTR_API ARaceGameMode : public AGameModeBase
{
	GENERATED_BODY()

	TSet<AJet*> runningJets;
	UWorld* gameWorld;

protected:

	UPROPERTY()
		int numberOfPlayers;
	
	UFUNCTION()
		void actorReadyToStore(const FActorsInitializedParams& parameters);
public:
	ARaceGameMode();
	
	void StartPlay() override;

	int jetsToSpawn();
	TSet<AJet*> jetsInPlay();
};
