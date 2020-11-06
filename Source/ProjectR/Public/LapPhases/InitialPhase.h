// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LapPhases/LapPhase.h"
#include "InitialPhase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API AInitialPhase : public ALapPhase
{
	GENERATED_BODY()

public:
	ALapPhase* updatePhase(ALapPhase* anotherPhase) override;
};
