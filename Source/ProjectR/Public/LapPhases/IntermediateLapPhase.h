// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LapPhases/LapPhase.h"
#include "IntermediateLapPhase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API AIntermediateLapPhase : public ALapPhase
{
	GENERATED_BODY()

public:
	
	bool isNextPhase(ALapPhase* aPhase) override;
};
