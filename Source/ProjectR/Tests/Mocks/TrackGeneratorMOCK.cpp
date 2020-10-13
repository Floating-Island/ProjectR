// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackGeneratorMOCK.h"
#include "Components/SplineComponent.h"

bool ATrackGeneratorMOCK::hasSplineComponent()
{
	return splineComponent ? true : false;
}

bool ATrackGeneratorMOCK::splineIsRootComponent()
{
	return RootComponent == splineComponent ? true : false;
}

int32 ATrackGeneratorMOCK::splineMeshesQuantity()
{
	return splineComponent->GetNumberOfSplinePoints();
}
