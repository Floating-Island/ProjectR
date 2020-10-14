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

bool ATrackGeneratorMOCK::sameNumberOfMeshesThanPoints()
{
	return splineMeshesQuantity() == splinePointsQuantity();
}

bool ATrackGeneratorMOCK::MeshesAndPointsHaveSameStartPositions()
{
	if (!sameNumberOfMeshesThanPoints())
	{
		return false;
	}

	for (int32 splinePointIndex = 0; splinePointIndex < splinePointsQuantity(); ++splinePointIndex)
	{
		FVector currentSplinePointPosition = splineComponent->GetLocationAtSplinePoint(splinePointIndex, ESplineCoordinateSpace::World);
		FVector currentSplineMeshPosition = (splineMeshes[splinePointIndex])->GetStartPosition();

		UE_LOG(LogTemp, Log, TEXT("Spline point position: %s."), *currentSplinePointPosition.ToString());
		UE_LOG(LogTemp, Log, TEXT("Spline mesh start position: %s."), *currentSplineMeshPosition.ToString());

		if (!currentSplineMeshPosition.Equals(currentSplinePointPosition))
		{
			UE_LOG(LogTemp, Log, TEXT("Spline mesh start position doesn't match spline point position."));
			return false;
		}
	}

	return true;
}

bool ATrackGeneratorMOCK::MeshesAndPointsHaveSameEndPositions()
{
	if (!sameNumberOfMeshesThanPoints())
	{
		return false;
	}

	for (int32 splinePointIndex = 0; splinePointIndex < splinePointsQuantity(); ++splinePointIndex)
	{
		FVector nextSplinePointPosition = splineComponent->GetLocationAtSplinePoint(nextSplineIndex(splinePointIndex), ESplineCoordinateSpace::World);
		FVector currentSplineMeshPosition = (splineMeshes[splinePointIndex])->GetEndPosition();

		UE_LOG(LogTemp, Log, TEXT("Spline point position: %s."), *nextSplinePointPosition.ToString());
		UE_LOG(LogTemp, Log, TEXT("Spline mesh end position: %s."), *currentSplineMeshPosition.ToString());

		if (!currentSplineMeshPosition.Equals(nextSplinePointPosition))
		{
			UE_LOG(LogTemp, Log, TEXT("Spline mesh end position doesn't match spline point position."));
			return false;
		}
	}

	return true;
}



bool ATrackGeneratorMOCK::MeshesAndPointsHaveSameStartTangents()
{
	if (!sameNumberOfMeshesThanPoints())
	{
		return false;
	}

	for (int32 splinePointIndex = 0; splinePointIndex < splinePointsQuantity(); ++splinePointIndex)
	{
		FVector currentSplinePointTangent = splineComponent->GetTangentAtSplinePoint(splinePointIndex, ESplineCoordinateSpace::World);
		FVector currentSplineMeshTangent = (splineMeshes[splinePointIndex])->GetStartTangent();

		UE_LOG(LogTemp, Log, TEXT("Spline point tangent: %s."), *currentSplinePointTangent.ToString());
		UE_LOG(LogTemp, Log, TEXT("Spline mesh start tangent: %s."), *currentSplineMeshTangent.ToString());

		if (!currentSplineMeshTangent.Equals(currentSplinePointTangent))
		{
			UE_LOG(LogTemp, Log, TEXT("Spline mesh start tangent doesn't match spline point tangent."));
			return false;
		}
	}

	return true;
}
