// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LapPhases/LapPhase.h"
#include "LapPhaseMOCK.generated.h"

/**
 *
 */
UCLASS()
class PROJECTR_API ALapPhaseMOCK : public ALapPhase
{
	GENERATED_BODY()

public:
	bool hasAStaticMeshComponent();
	bool hasAStaticMeshAssociated();
	bool phaseWallIsRootComponent();
	bool hasCollisionEnabledToQueryOnly();
};
