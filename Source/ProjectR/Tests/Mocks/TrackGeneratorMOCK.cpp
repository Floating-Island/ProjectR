// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackGeneratorMOCK.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Engine/EngineTypes.h"

bool ATrackGeneratorMOCK::hasSplineComponent()
{
	return splineComponent ? true : false;
}

bool ATrackGeneratorMOCK::splineIsRootComponent()
{
	return RootComponent == splineComponent ? true : false;
}

int32 ATrackGeneratorMOCK::roadSplinesQuantity()
{
	return roadSplines.Num();
}

int32 ATrackGeneratorMOCK::splinePointsQuantity()
{
	return splineComponent->GetNumberOfSplinePoints();
}

bool ATrackGeneratorMOCK::sameNumberOfRoadSplinesThanPoints()
{
	return roadSplinesQuantity() == splinePointsQuantity();
}

bool ATrackGeneratorMOCK::roadSplinesAndPointsHaveSameStartPositions()
{
	if (!sameNumberOfRoadSplinesThanPoints())
	{
		return false;
	}

	for (int32 splinePointIndex = 0; splinePointIndex < splinePointsQuantity(); ++splinePointIndex)
	{
		FVector currentSplinePointPosition = splineComponent->GetLocationAtSplinePoint(splinePointIndex, ESplineCoordinateSpace::Local);
		FVector currentRoadSplinePosition = (roadSplines[splinePointIndex])->GetStartPosition();

		UE_LOG(LogTemp, Log, TEXT("Spline point position: %s."), *currentSplinePointPosition.ToString());
		UE_LOG(LogTemp, Log, TEXT("Road spline start position: %s."), *currentRoadSplinePosition.ToString());

		if (!currentRoadSplinePosition.Equals(currentSplinePointPosition))
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline start position doesn't match spline point position."));
			return false;
		}
	}

	return true;
}

bool ATrackGeneratorMOCK::roadSplinesAndPointsHaveSameEndPositions()
{
	if (!sameNumberOfRoadSplinesThanPoints())
	{
		return false;
	}

	for (int32 splinePointIndex = 0; splinePointIndex < splinePointsQuantity(); ++splinePointIndex)
	{
		FVector nextSplinePointPosition = splineComponent->GetLocationAtSplinePoint(nextSplineIndexOf(splinePointIndex), ESplineCoordinateSpace::Local);
		FVector currentRoadSplinePosition = (roadSplines[splinePointIndex])->GetEndPosition();

		UE_LOG(LogTemp, Log, TEXT("Spline point position: %s."), *nextSplinePointPosition.ToString());
		UE_LOG(LogTemp, Log, TEXT("Road spline end position: %s."), *currentRoadSplinePosition.ToString());

		if (!currentRoadSplinePosition.Equals(nextSplinePointPosition))
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline end position doesn't match next spline point position."));
			return false;
		}
	}

	return true;
}



bool ATrackGeneratorMOCK::roadSplinesAndPointsHaveSameStartTangents()
{
	if (!sameNumberOfRoadSplinesThanPoints())
	{
		return false;
	}

	for (int32 splinePointIndex = 0; splinePointIndex < splinePointsQuantity(); ++splinePointIndex)
	{
		FVector currentSplinePointTangent = splineComponent->GetTangentAtSplinePoint(splinePointIndex, ESplineCoordinateSpace::Local);
		FVector currentRoadSplineTangent = (roadSplines[splinePointIndex])->GetStartTangent();

		UE_LOG(LogTemp, Log, TEXT("Spline point tangent: %s."), *currentSplinePointTangent.ToString());
		UE_LOG(LogTemp, Log, TEXT("Road spline start tangent: %s."), *currentRoadSplineTangent.ToString());

		if (!currentRoadSplineTangent.Equals(currentSplinePointTangent))
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline start tangent doesn't match spline point tangent."));
			return false;
		}
	}

	return true;
}

bool ATrackGeneratorMOCK::roadSplinesAndPointsHaveSameEndTangents()
{
	if (!sameNumberOfRoadSplinesThanPoints())
	{
		return false;
	}

	for (int32 splinePointIndex = 0; splinePointIndex < splinePointsQuantity(); ++splinePointIndex)
	{
		FVector nextSplinePointTangent = splineComponent->GetTangentAtSplinePoint(nextSplineIndexOf(splinePointIndex), ESplineCoordinateSpace::Local);
		FVector currentRoadSplineTangent = (roadSplines[splinePointIndex])->GetEndTangent();

		UE_LOG(LogTemp, Log, TEXT("Spline point tangent: %s."), *nextSplinePointTangent.ToString());
		UE_LOG(LogTemp, Log, TEXT("Road spline end tangent: %s."), *currentRoadSplineTangent.ToString());

		if (!currentRoadSplineTangent.Equals(nextSplinePointTangent))
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline end tangent doesn't match next spline point tangent."));
			return false;
		}
	}

	return true;
}

bool ATrackGeneratorMOCK::roadSplinesHaveMeshesSet()
{
	for (auto roadSpline : roadSplines)
	{
		if (!roadSpline->GetStaticMesh())
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline doesn't have static mesh set."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::roadSplinesMeshesAreRoadMesh()
{
	for (auto roadSpline : roadSplines)
	{
		UStaticMesh* mesh = roadSpline->GetStaticMesh();
		if (!mesh)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline doesn't have static mesh set."));
			return false;
		}
		if (mesh != roadMesh)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline static mesh isn't the road mesh."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::magnetSplinesQuantitySameAsSplinePoints()
{
	return static_cast<int32>(magnetSplines.Num()) == splinePointsQuantity();
}

bool ATrackGeneratorMOCK::roadSplinesHaveCollisionEnabledSetToQueryAndPhysics()
{
	for (auto roadSpline : roadSplines)
	{
		if (!roadSpline)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline is nullptr."));
			return false;
		}
		if (roadSpline->GetCollisionEnabled() != ECollisionEnabled::QueryAndPhysics)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline doesn't have collision enabled."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::roadSplinesHaveCollisionObjectToWorldStatic()
{
	for (auto roadSpline : roadSplines)
	{
		if (!roadSpline)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline is nullptr."));
			return false;
		}
		if (roadSpline->GetCollisionObjectType() != ECollisionChannel::ECC_WorldStatic)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline isn't of type world static."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::roadSplinesAreAttachedToRoot()
{
	for (auto roadSpline : roadSplines)
	{
		if (!roadSpline)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline is nullptr."));
			return false;
		}
		if (roadSpline->GetAttachParent() != RootComponent)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline isn't attached to root component."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::roadSplinesMobilitySameAsRoot()
{
	for (auto roadSpline : roadSplines)
	{
		if (!roadSpline)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline is nullptr."));
			return false;
		}
		if (roadSpline->Mobility != RootComponent->Mobility)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline doesn't have same mobility as root."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::isSplineComponentLooping()
{
	return splineComponent->IsClosedLoop();
}

bool ATrackGeneratorMOCK::magnetSplinesAreAttachedToRoadSplines()
{
	for (int atIndex = 0; atIndex < roadSplines.Num(); ++atIndex)
	{
		if (!roadSplines[atIndex] || !magnetSplines[atIndex])
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline or magnet spline is nullptr."));
			return false;
		}
		if (magnetSplines[atIndex]->GetAttachParent() != roadSplines[atIndex])
		{
			UE_LOG(LogTemp, Log, TEXT("Magnet spline at index %d isn't attached to road spline."), atIndex);
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::magnetSplinesMobilitySameAsRoadSplines()
{
	for (int atIndex = 0; atIndex < roadSplines.Num(); ++atIndex)
	{
		if (!roadSplines[atIndex] || !magnetSplines[atIndex])
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline or magnet spline is nullptr."));
			return false;
		}
		if (magnetSplines[atIndex]->Mobility != roadSplines[atIndex]->Mobility)
		{
			UE_LOG(LogTemp, Log, TEXT("Magnet spline at index %d doesn't have the same mobility as the road spline."), atIndex);
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::magnetSplinesOnTopOfRoadSplines()
{
	for (int atIndex = 0; atIndex < roadSplines.Num(); ++atIndex)
	{
		if (!roadSplines[atIndex] || !magnetSplines[atIndex])
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline or magnet spline is nullptr."));
			return false;
		}
		float magnetSplineStartDistance = (magnetSplines[atIndex]->GetStartPosition() - roadSplines[atIndex]->GetStartPosition()).Size();
		float magnetSplineEndDistance = (magnetSplines[atIndex]->GetEndPosition() - roadSplines[atIndex]->GetEndPosition()).Size();
		if (!FMath::IsNearlyEqual(magnetSplineStartDistance, magnetSplineHeightDistanceToRoadSpline, 0.001f) || !FMath::IsNearlyEqual(magnetSplineEndDistance, magnetSplineHeightDistanceToRoadSpline, 0.001f))
		{
			UE_LOG(LogTemp, Log, TEXT("Magnet spline at index %d isn't located at the specified height distance from the road spline."), atIndex);
			UE_LOG(LogTemp, Log, TEXT("Magnet spline start position: %s."), *magnetSplines[atIndex]->GetStartPosition().ToString());
			UE_LOG(LogTemp, Log, TEXT("Road spline start position: %s."), *roadSplines[atIndex]->GetStartPosition().ToString());
			UE_LOG(LogTemp, Log, TEXT("Magnet spline end position: %s."), *magnetSplines[atIndex]->GetEndPosition().ToString());
			UE_LOG(LogTemp, Log, TEXT("Road spline end position: %s."), *roadSplines[atIndex]->GetEndPosition().ToString());
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::magnetSplinesAndPointsHaveSameTangents()
{
	if (!magnetSplinesQuantitySameAsSplinePoints())
	{
		return false;
	}

	for (int32 splinePointIndex = 0; splinePointIndex < splinePointsQuantity(); ++splinePointIndex)
	{
		FVector magnetSplineStartTangent = (magnetSplines[splinePointIndex])->GetStartTangent();
		FVector magnetSplineEndTangent = (magnetSplines[splinePointIndex])->GetEndTangent();
		FVector currentSplinePointTangent = splineComponent->GetTangentAtSplinePoint(splinePointIndex, ESplineCoordinateSpace::Local);
		FVector nextSplinePointTangent = splineComponent->GetTangentAtSplinePoint(nextSplineIndexOf(splinePointIndex), ESplineCoordinateSpace::Local);

		UE_LOG(LogTemp, Log, TEXT("current spline point tangent: %s."), *currentSplinePointTangent.ToString());
		UE_LOG(LogTemp, Log, TEXT("Magnet spline start tangent: %s."), *magnetSplineStartTangent.ToString());
		UE_LOG(LogTemp, Log, TEXT("Next spline point tangent: %s."), *nextSplinePointTangent.ToString());
		UE_LOG(LogTemp, Log, TEXT("Magnet spline end tangent: %s."), *magnetSplineEndTangent.ToString());

		if (!magnetSplineStartTangent.Equals(currentSplinePointTangent) || !magnetSplineEndTangent.Equals(nextSplinePointTangent))
		{
			UE_LOG(LogTemp, Log, TEXT("Magnet spline tangents don't match spline point tangents."));
			return false;
		}
	}

	return true;
}

bool ATrackGeneratorMOCK::magnetSplinesHaveMeshesSet()
{
	for (auto magnetSpline : magnetSplines)
	{
		if (!magnetSpline->GetStaticMesh())
		{
			UE_LOG(LogTemp, Log, TEXT("Magnet spline doesn't have static mesh set."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::magnetSplinesAreHiddenInGame()
{
	for (auto magnetSpline : magnetSplines)
	{
		if (!magnetSpline->bHiddenInGame)
		{
			UE_LOG(LogTemp, Log, TEXT("Magnet spline isn't set to be hidden in game."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::collisionEnabledToQueryOnlyOnMagnetSplines()
{
	for (auto magnetSpline : magnetSplines)
	{
		if (magnetSpline->GetCollisionEnabled() != ECollisionEnabled::QueryOnly)
		{
			UE_LOG(LogTemp, Log, TEXT("Magnet spline isn't set to have collisions enabled to query only."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::magnetSplinesOverlapWithPawnChannel()
{
	for (auto magnetSpline : magnetSplines)
	{
		if (magnetSpline->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) != ECollisionResponse::ECR_Overlap)
		{
			UE_LOG(LogTemp, Log, TEXT("Magnet spline isn't set to overlap with the pawn channel."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::magnetSplinesGenerateOverlapEvents()
{
	for (auto magnetSpline : magnetSplines)
	{
		if (!magnetSpline->GetGenerateOverlapEvents())
		{
			UE_LOG(LogTemp, Log, TEXT("Magnet spline isn't set to generate overlap events."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::componentsHaveSmoothInterpolation()
{
	for (int32 splinePointIndex = 0; splinePointIndex < splinePointsQuantity(); ++splinePointIndex)
	{
		bool magnetSplineWithSmoothInterpolation = magnetSplines[splinePointIndex]->bSmoothInterpRollScale;
		bool roadSplineWithSmoothInterpolation = roadSplines[splinePointIndex]->bSmoothInterpRollScale;

		UE_LOG(LogTemp, Log, TEXT("Road spline has smooth interpolation: %s."), *FString(roadSplineWithSmoothInterpolation ? "true" : "false"));
		UE_LOG(LogTemp, Log, TEXT("Magnet spline has smooth interpolation: %s."), *FString(magnetSplineWithSmoothInterpolation ? "true" : "false"));

		if (!roadSplineWithSmoothInterpolation || !magnetSplineWithSmoothInterpolation)
		{
			UE_LOG(LogTemp, Log, TEXT("Components don't have smooth interpolation enabled."));
			return false;
		}
	}

	return true;
}

bool ATrackGeneratorMOCK::sameAmountOfRollsThanSplinePoints()
{
	return rollArray.Num() == splinePointsQuantity();
}

void ATrackGeneratorMOCK::rollSplines(float rollValue)
{
	for(auto roll : rollArray)
	{
		roll = rollValue;
	}
}

bool ATrackGeneratorMOCK::splineMeshComponentsRollIs(float aRollValue)
{
	for (int32 splinePointIndex = 0; splinePointIndex < splinePointsQuantity(); ++splinePointIndex)
	{
		float roadStartRoll = roadSplines[splinePointIndex]->GetStartRoll();
		float roadEndRoll = roadSplines[splinePointIndex]->GetEndRoll();
		float magnetStartRoll = magnetSplines[splinePointIndex]->GetStartRoll();
		float magnetEndRoll = magnetSplines[splinePointIndex]->GetEndRoll();

		UE_LOG(LogTemp, Log, TEXT("Specified roll: %f."), aRollValue);
		UE_LOG(LogTemp, Log, TEXT("Spline point index: %d."), splinePointIndex);
		UE_LOG(LogTemp, Log, TEXT("Road spline start roll: %f."), roadStartRoll);
		UE_LOG(LogTemp, Log, TEXT("Road spline end roll: %f."), roadEndRoll);
		UE_LOG(LogTemp, Log, TEXT("Magnet spline start roll: %f."), magnetStartRoll);
		UE_LOG(LogTemp, Log, TEXT("Magnet spline end roll: %f."), magnetEndRoll);

		bool roadStartRollSimillarToSpecified = FMath::IsNearlyEqual(roadStartRoll, aRollValue);
		bool roadEndRollSimillarToSpecified = FMath::IsNearlyEqual(roadEndRoll, aRollValue);
		bool magnetStartRollSimillarToSpecified = FMath::IsNearlyEqual(magnetStartRoll, aRollValue);
		bool magnetEndRollSimillarToSpecified = FMath::IsNearlyEqual(magnetEndRoll, aRollValue);

		if (!roadStartRollSimillarToSpecified || !roadEndRollSimillarToSpecified || !magnetStartRollSimillarToSpecified || !magnetEndRollSimillarToSpecified)
		{
			UE_LOG(LogTemp, Log, TEXT("Components don't have roll similar to the specified."));
			return false;
		}
	}
	return true;
}




