// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/RaceGameMode.h"
#include "RaceGameModeMOCK.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API ARaceGameModeMOCK : public ARaceGameMode
{
	GENERATED_BODY()
public:
	void StartPlay() override;
};
