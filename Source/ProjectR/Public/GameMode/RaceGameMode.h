// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RaceGameMode.generated.h"

class AJet;
/**
 * 
 */
UCLASS()
class PROJECTR_API ARaceGameMode : public AGameModeBase
{
	GENERATED_BODY()

	TSet<AJet*> runningJets;
public:
	void StartPlay() override;

	TSet<AJet*> jetsInPlay();
};
