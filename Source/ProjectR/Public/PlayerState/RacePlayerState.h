// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RacePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API ARacePlayerState : public APlayerState
{
	GENERATED_BODY()

protected:

	
	int lap;

public:
	ARacePlayerState();
	int currentLap();
	void updateLapTo(int aCurrentLap);
	
};
