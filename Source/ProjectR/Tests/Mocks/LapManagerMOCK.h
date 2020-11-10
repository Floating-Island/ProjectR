// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LapManager/LapManager.h"
#include "LapManagerMOCK.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API ALapManagerMOCK : public ALapManager
{
	GENERATED_BODY()

public:
	bool defaultLapPhaseIsInitialLapPhase();
	bool InitialLapCountSetToOne();
	bool jetsMovedFromInitialToIntermediatePhase();
	void makeJetsPhaseIntermediate();
	bool jetsMovedFromIntermediateToFinalPhase();
	void makeJetsPhaseFinal();
	bool jetsMovedFromFinalToInitialPhase();
};
