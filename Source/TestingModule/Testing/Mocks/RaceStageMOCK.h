// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/RaceStages/RaceStage.h"
#include "RaceStageMOCK.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGMODULE_API ARaceStageMOCK : public ARaceStage
{
	GENERATED_BODY()

public:
	bool raceModeIsSubscribed();
};
