// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Track/TrackGenerator.h"
#include "TrackGeneratorMOCK.generated.h"

/**
 *
 */
UCLASS()
class TESTINGMODULE_API ATrackGeneratorMOCK : public ATrackGenerator
{
	GENERATED_BODY()
public:
	bool hasSplineComponent();
	bool splineIsRootComponent();
	int32 roadSplinesQuantity();
	int32 boundsSplinesQuantity();
	int32 splinePointsQuantity();
	bool sameNumberOfRoadSplinesThanPoints();
	bool roadSplinesAndPointsHaveSameStartPositions();
	bool roadSplinesAndPointsHaveSameEndPositions();
	bool roadSplinesAndPointsHaveSameStartTangents();
	bool roadSplinesAndPointsHaveSameEndTangents();
	bool roadSplinesHaveMeshesSet();
	bool roadSplinesMeshesAreRoadMesh();
	bool magnetSplinesQuantitySameAsSplinePoints();
	bool roadSplinesHaveCollisionEnabledSetToQueryAndPhysics();
	bool roadSplinesHaveCollisionObjectToWorldStatic();
	bool roadSplinesAreAttachedToRoot();
	bool roadSplinesMobilitySameAsRoot();
	bool isSplineComponentLooping();
	bool magnetSplinesAreAttachedToRoadSplines();
	bool magnetSplinesMobilitySameAsRoadSplines();
	bool magnetSplinesOnTopOfRoadSplines();
	bool magnetSplinesAndPointsHaveSameTangents();
	bool magnetSplinesHaveMeshesSet();
	bool magnetSplinesAreHiddenInGame();
	bool collisionEnabledToQueryOnlyOnMagnetSplines();
	bool magnetSplinesOverlapWithPawnChannel();
	bool magnetSplinesGenerateOverlapEvents();
	bool componentsHaveSmoothInterpolation();
	bool sameAmountOfTrackSectionsThanSplinePoints();
	void rollSplines(float aRollValue);
	bool splineMeshComponentsRollIs(float aRollValue);
	void widenSplines(float aWidthValue);
	bool splineMeshComponentsWidthIs(float aWidthValue);
	void disableCollisions();
	bool splineMeshComponentsCollisionsDisabled();
	bool splineMeshComponentsExpectedCollisions();

	bool boundsSplinesAreAttachedToRoadSplines();
	bool boundsSplinesMobilitySameAsRoadSplines();
	bool boundsSplinesAndPointsHaveSameTangents();
	bool boundsSplinesHaveMeshesSet();
	bool boundsSplinesAreHiddenInGame();
	bool boundsSplinesHaveSmoothInterpolation();
	bool boundsSplinesHaveSameRollAs(float aRollValue);
	bool boundsSplinesHaveSameWidthAs(float aWidthValue);
	bool boundsSplinesCollisionsDisabled();
	bool boundsSplinesCollisionsAsQueryAndPhysics();
};
