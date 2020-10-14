// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackGeneratorMOCK.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

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
	return splineMeshes.Num();
}

int32 ATrackGeneratorMOCK::splinePointsQuantity()
{
	return splineComponent->GetNumberOfSplinePoints();
}

bool ATrackGeneratorMOCK::MeshesAndPointsHaveSameStartPositions()
{
	bool haveSameQuantityOfMembers = splineMeshesQuantity() == splinePointsQuantity();
	if (!haveSameQuantityOfMembers)
	{
		return false;
	}

	for (int32 splinePointIndex = 0; splinePointIndex < splinePointsQuantity(); ++splinePointIndex)
	{
		FVector currentSplinePointPosition = splineComponent->GetLocationAtSplinePoint(splinePointIndex, ESplineCoordinateSpace::World);
		FVector currentSplineMeshPosition = (splineMeshes[splinePointIndex])->GetComponentLocation();

		UE_LOG(LogTemp, Log, TEXT("Spline point position: %s."), *currentSplinePointPosition.ToString());
		UE_LOG(LogTemp, Log, TEXT("Spline mesh position: %s."), *currentSplineMeshPosition.ToString());
		
		if (!currentSplineMeshPosition.Equals(currentSplinePointPosition))
		{
			UE_LOG(LogTemp, Log, TEXT("Spline mesh position doesn't match spline point position."));
			return false;
		}
	}

	return true;
}
