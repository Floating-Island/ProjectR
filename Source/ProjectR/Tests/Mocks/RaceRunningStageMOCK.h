// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/RaceStages/RaceRunningStage.h"
#include "RaceRunningStageMOCK.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API ARaceRunningStageMOCK : public ARaceRunningStage
{
	GENERATED_BODY()


public:
	bool announcerRemovalDelayStarted();
};
