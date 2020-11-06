// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LapPhases/LapPhase.h"
#include "Lap.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API ALap : public ALapPhase
{
	GENERATED_BODY()

public:
	ALapPhase* updateState(ALapPhase* anotherPhase) override;
};
