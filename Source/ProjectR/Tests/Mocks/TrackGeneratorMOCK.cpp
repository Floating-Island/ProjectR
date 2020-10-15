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
		FVector currentSplinePointPosition = splineComponent->GetLocationAtSplinePoint(splinePointIndex, ESplineCoordinateSpace::Local);
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
		FVector nextSplinePointPosition = splineComponent->GetLocationAtSplinePoint(nextSplineIndex(splinePointIndex), ESplineCoordinateSpace::Local);
		FVector currentSplineMeshPosition = (splineMeshes[splinePointIndex])->GetEndPosition();

		UE_LOG(LogTemp, Log, TEXT("Spline point position: %s."), *nextSplinePointPosition.ToString());
		UE_LOG(LogTemp, Log, TEXT("Spline mesh end position: %s."), *currentSplineMeshPosition.ToString());

		if (!currentSplineMeshPosition.Equals(nextSplinePointPosition))
		{
			UE_LOG(LogTemp, Log, TEXT("Spline mesh end position doesn't match next spline point position."));
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
		FVector currentSplinePointTangent = splineComponent->GetTangentAtSplinePoint(splinePointIndex, ESplineCoordinateSpace::Local);
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

bool ATrackGeneratorMOCK::MeshesAndPointsHaveSameEndTangents()
{
	if (!sameNumberOfMeshesThanPoints())
	{
		return false;
	}

	for (int32 splinePointIndex = 0; splinePointIndex < splinePointsQuantity(); ++splinePointIndex)
	{
		FVector nextSplinePointTangent = splineComponent->GetTangentAtSplinePoint(nextSplineIndex(splinePointIndex), ESplineCoordinateSpace::Local);
		FVector currentSplineMeshTangent = (splineMeshes[splinePointIndex])->GetEndTangent();

		UE_LOG(LogTemp, Log, TEXT("Spline point tangent: %s."), *nextSplinePointTangent.ToString());
		UE_LOG(LogTemp, Log, TEXT("Spline mesh end tangent: %s."), *currentSplineMeshTangent.ToString());

		if (!currentSplineMeshTangent.Equals(nextSplinePointTangent))
		{
			UE_LOG(LogTemp, Log, TEXT("Spline mesh end tangent doesn't match next spline point tangent."));
			return false;
		}
	}

	return true;
}

bool ATrackGeneratorMOCK::splineMeshesHaveMeshesSet()
{
	for (auto splineMesh : splineMeshes)
	{
		if (!splineMesh->GetStaticMesh())
		{
			UE_LOG(LogTemp, Log, TEXT("Spline mesh doesn't have static mesh set."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::splineMeshesMeshesAreRoadMesh()
{
	for (auto splineMesh : splineMeshes)
	{
		UStaticMesh* mesh = splineMesh->GetStaticMesh();
		if (!mesh)
		{
			UE_LOG(LogTemp, Log, TEXT("Spline mesh doesn't have static mesh set."));
			return false;
		}
		if (mesh != roadMesh)
		{
			UE_LOG(LogTemp, Log, TEXT("Spline mesh static mesh isn't the road mesh."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::MagnetBoxesQuantitySameAsSplinePoints()
{
	return static_cast<int32>(magnetBoxes.Num()) == splinePointsQuantity();
}

bool ATrackGeneratorMOCK::splineMeshesHaveCollisionEnabled()
{
	for (auto splineMesh : splineMeshes)
	{
		if (!splineMesh)
		{
			UE_LOG(LogTemp, Log, TEXT("Spline mesh is nullptr."));
			return false;
		}
		if (splineMesh->GetCollisionEnabled() != ECollisionEnabled::QueryAndPhysics)
		{
			UE_LOG(LogTemp, Log, TEXT("Spline mesh doesn't have collision enabled."));
			return false;
		}
	}
	return true;
}


