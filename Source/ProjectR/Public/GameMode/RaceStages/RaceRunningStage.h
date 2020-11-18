// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/RaceStages/RaceStage.h"
#include "RaceRunningStage.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API ARaceRunningStage : public ARaceStage
{
	GENERATED_BODY()

public:
	ARaceStage* nextStage() override;
	void Tick(float DeltaSeconds) override;
};
