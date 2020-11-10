// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LapPhases/LapPhase.h"
#include "FinalLapPhase.generated.h"

/**
 *
 */
UCLASS()
class PROJECTR_API AFinalLapPhase : public ALapPhase
{
	GENERATED_BODY()

public:

	bool nextPhaseIs(ALapPhase* aPhase) override;

	bool comesFromIntermediateLapPhase() override;
};
