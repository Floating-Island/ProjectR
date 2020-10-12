// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackGeneratorMOCK.h"

bool ATrackGeneratorMOCK::hasSplineComponent()
{
	return splineComponent ? true : false;
}

bool ATrackGeneratorMOCK::splineIsRootComponent()
{
	return RootComponent == Cast<USceneComponent, USplineComponent>(splineComponent)? true : false;
}
