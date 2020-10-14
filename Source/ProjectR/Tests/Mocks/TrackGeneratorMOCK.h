// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Track/TrackGenerator.h"
#include "TrackGeneratorMOCK.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API ATrackGeneratorMOCK : public ATrackGenerator
{
	GENERATED_BODY()
public:
	bool hasSplineComponent();
	bool splineIsRootComponent();
	int32 splineMeshesQuantity();
    int32 splinePointsQuantity();
	bool MeshesAndPointsHaveSameStartPositions();
	bool MeshesAndPointsHaveSameEndPositions();
};
