// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/RaceStages/RaceBeginningStage.h"
#include "RaceBeginningStageMOCK.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API ARaceBeginningStageMOCK : public ARaceBeginningStage
{
	GENERATED_BODY()

public:
	bool hasTimerActive();
};
