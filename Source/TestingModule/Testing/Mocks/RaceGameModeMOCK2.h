// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/RaceGameMode.h"
#include "RaceGameModeMOCK2.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGMODULE_API ARaceGameModeMOCK2 : public ARaceGameMode
{
	GENERATED_BODY()
public:
	void StartPlay() override;

	void changeStageTo(ARaceStage* anotherStage);

	ARaceStage* currentStage();

	void addToRunningJets(AJet* aJet);

	void createLapManagerMOCK();
};
