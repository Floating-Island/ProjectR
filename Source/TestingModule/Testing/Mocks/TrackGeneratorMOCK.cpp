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
	return trackSections.Num();
}

int32 ATrackGeneratorMOCK::boundsSplinesQuantity()
{
	int numberOfBounds = 0;
	for( int position =0 ; position < trackSections.Num(); ++position)
	{
		if(trackSections[position].boundsSpline != nullptr)
		{
			++numberOfBounds;
		}
	}
	return numberOfBounds;
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
		FVector currentRoadSplinePosition = trackSections[splinePointIndex].roadSpline->GetStartPosition();

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
		FVector currentRoadSplinePosition = trackSections[splinePointIndex].roadSpline->GetEndPosition();

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
		FVector currentRoadSplineTangent = trackSections[splinePointIndex].roadSpline->GetStartTangent();

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
		FVector currentRoadSplineTangent = trackSections[splinePointIndex].roadSpline->GetEndTangent();

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
	for (const auto& trackSection : trackSections)
	{
		if (!trackSection.roadSpline->GetStaticMesh())
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline doesn't have static mesh set."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::roadSplinesMeshesAreRoadMesh()
{
	for (const auto& trackSection : trackSections)
	{
		UStaticMesh* mesh = trackSection.roadSpline->GetStaticMesh();
		if (!mesh)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline doesn't have static mesh set."));
			return false;
		}
		if (mesh != defaultRoadMesh)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline static mesh isn't the road mesh."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::magnetSplinesQuantitySameAsSplinePoints()
{
	return static_cast<int32>(trackSections.Num()) == splinePointsQuantity();
}

bool ATrackGeneratorMOCK::roadSplinesHaveCollisionEnabledSetToQueryAndPhysics()
{
	for (const auto& trackSection : trackSections)
	{
		if (!trackSection.roadSpline)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline is nullptr."));
			return false;
		}
		if (trackSection.roadSpline->GetCollisionEnabled() != ECollisionEnabled::QueryAndPhysics)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline doesn't have collision enabled."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::roadSplinesHaveCollisionObjectToWorldStatic()
{
	for (const auto& trackSection : trackSections)
	{
		if (!trackSection.roadSpline)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline is nullptr."));
			return false;
		}
		if (trackSection.roadSpline->GetCollisionObjectType() != ECollisionChannel::ECC_WorldStatic)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline isn't of type world static."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::roadSplinesAreAttachedToRoot()
{
	for (const auto& trackSection : trackSections)
	{
		if (!trackSection.roadSpline)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline is nullptr."));
			return false;
		}
		if (trackSection.roadSpline->GetAttachParent() != RootComponent)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline isn't attached to root component."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::roadSplinesMobilitySameAsRoot()
{
	for (const auto& trackSection : trackSections)
	{
		if (!trackSection.roadSpline)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline is nullptr."));
			return false;
		}
		if (trackSection.roadSpline->Mobility != RootComponent->Mobility)
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
	for (const auto& trackSection : trackSections)
	{
		if (!trackSection.roadSpline || !trackSection.magnetSpline)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline or magnet spline is nullptr."));
			return false;
		}
		if (trackSection.magnetSpline->GetAttachParent() != trackSection.roadSpline)
		{
			UE_LOG(LogTemp, Log, TEXT("Magnet spline isn't attached to road spline."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::magnetSplinesMobilitySameAsRoadSplines()
{
	for (const auto& trackSection : trackSections)
	{
		if (!trackSection.roadSpline || !trackSection.magnetSpline)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline or magnet spline is nullptr."));
			return false;
		}
		if (trackSection.magnetSpline->Mobility != trackSection.roadSpline->Mobility)
		{
			UE_LOG(LogTemp, Log, TEXT("Magnet spline at doesn't have the same mobility as the road spline."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::magnetSplinesOnTopOfRoadSplines()
{
	for (const auto& trackSection : trackSections)
	{
		if (!trackSection.roadSpline || !trackSection.magnetSpline)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline or magnet spline is nullptr."));
			return false;
		}
		float magnetSplineStartDistance = (trackSection.magnetSpline->GetStartPosition() - trackSection.roadSpline->GetStartPosition()).Size();
		float magnetSplineEndDistance = (trackSection.magnetSpline->GetEndPosition() - trackSection.roadSpline->GetEndPosition()).Size();
		if (!FMath::IsNearlyEqual(magnetSplineStartDistance, magnetSplineHeightDistanceToRoadSpline, 0.001f) || !FMath::IsNearlyEqual(magnetSplineEndDistance, magnetSplineHeightDistanceToRoadSpline, 0.001f))
		{
			UE_LOG(LogTemp, Log, TEXT("Magnet spline isn't located at the specified height distance from the road spline."));
			UE_LOG(LogTemp, Log, TEXT("Magnet spline start position: %s."), *trackSection.magnetSpline->GetStartPosition().ToString());
			UE_LOG(LogTemp, Log, TEXT("Road spline start position: %s."), *trackSection.roadSpline->GetStartPosition().ToString());
			UE_LOG(LogTemp, Log, TEXT("Magnet spline end position: %s."), *trackSection.magnetSpline->GetEndPosition().ToString());
			UE_LOG(LogTemp, Log, TEXT("Road spline end position: %s."), *trackSection.roadSpline->GetEndPosition().ToString());
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

	int index = 0;
	for (const auto& trackSection : trackSections)
	{
		FVector magnetSplineStartTangent = (trackSection.magnetSpline)->GetStartTangent();
		FVector magnetSplineEndTangent = (trackSection.magnetSpline)->GetEndTangent();
		FVector currentSplinePointTangent = splineComponent->GetTangentAtSplinePoint(index, ESplineCoordinateSpace::Local);
		FVector nextSplinePointTangent = splineComponent->GetTangentAtSplinePoint(nextSplineIndexOf(index), ESplineCoordinateSpace::Local);

		UE_LOG(LogTemp, Log, TEXT("current spline point tangent: %s."), *currentSplinePointTangent.ToString());
		UE_LOG(LogTemp, Log, TEXT("Magnet spline start tangent: %s."), *magnetSplineStartTangent.ToString());
		UE_LOG(LogTemp, Log, TEXT("Next spline point tangent: %s."), *nextSplinePointTangent.ToString());
		UE_LOG(LogTemp, Log, TEXT("Magnet spline end tangent: %s."), *magnetSplineEndTangent.ToString());

		if (!magnetSplineStartTangent.Equals(currentSplinePointTangent) || !magnetSplineEndTangent.Equals(nextSplinePointTangent))
		{
			UE_LOG(LogTemp, Log, TEXT("Magnet spline tangents don't match spline point tangents."));
			return false;
		}
		++index;
	}

	return true;
}

bool ATrackGeneratorMOCK::magnetSplinesHaveMeshesSet()
{
	for (const auto& trackSection : trackSections)
	{
		if (!trackSection.magnetSpline->GetStaticMesh())
		{
			UE_LOG(LogTemp, Log, TEXT("Magnet spline doesn't have static mesh set."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::magnetSplinesAreHiddenInGame()
{
	for (const auto& trackSection : trackSections)
	{
		if (!trackSection.magnetSpline->bHiddenInGame)
		{
			UE_LOG(LogTemp, Log, TEXT("Magnet spline isn't set to be hidden in game."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::collisionEnabledToQueryOnlyOnMagnetSplines()
{
	for (const auto& trackSection : trackSections)
	{
		if (trackSection.magnetSpline->GetCollisionEnabled() != ECollisionEnabled::QueryOnly)
		{
			UE_LOG(LogTemp, Log, TEXT("Magnet spline isn't set to have collisions enabled to query only."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::magnetSplinesOverlapWithPawnChannel()
{
	for (const auto& trackSection : trackSections)
	{
		if (trackSection.magnetSpline->GetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn) != ECollisionResponse::ECR_Overlap)
		{
			UE_LOG(LogTemp, Log, TEXT("Magnet spline isn't set to overlap with the pawn channel."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::magnetSplinesGenerateOverlapEvents()
{
	for (const auto& trackSection : trackSections)
	{
		if (!trackSection.magnetSpline->GetGenerateOverlapEvents())
		{
			UE_LOG(LogTemp, Log, TEXT("Magnet spline isn't set to generate overlap events."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::componentsHaveSmoothInterpolation()
{
	for (const auto& trackSection : trackSections)
	{
		bool magnetSplineWithSmoothInterpolation = trackSection.magnetSpline->bSmoothInterpRollScale;
		bool roadSplineWithSmoothInterpolation = trackSection.roadSpline->bSmoothInterpRollScale;

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

bool ATrackGeneratorMOCK::sameAmountOfTrackSectionsThanSplinePoints()
{
	return trackSections.Num() == splinePointsQuantity();
}

void ATrackGeneratorMOCK::rollSplines(float aRollValue)
{
	for (auto& trackSection : trackSections)
	{
		trackSection.startRoll = aRollValue;
	}
	UE_LOG(LogTemp, Log, TEXT("Roll has been set to: %f in the roll array. Now recreate the spline mesh components."), aRollValue);
	recreateSplineMeshComponents();
}

bool ATrackGeneratorMOCK::splineMeshComponentsRollIs(float aRollValue)
{
	int index = 0;
	for (const auto& trackSection : trackSections)
	{
		float roadStartRoll = trackSection.roadSpline->GetStartRoll();
		float roadEndRoll = trackSection.roadSpline->GetEndRoll();
		float magnetStartRoll = trackSection.magnetSpline->GetStartRoll();
		float magnetEndRoll = trackSection.magnetSpline->GetEndRoll();

		UE_LOG(LogTemp, Log, TEXT("Specified roll: %f."), aRollValue);
		UE_LOG(LogTemp, Log, TEXT("Spline point index: %d."), index);
		UE_LOG(LogTemp, Log, TEXT("Road spline start roll: %f."), roadStartRoll);
		UE_LOG(LogTemp, Log, TEXT("Road spline end roll: %f."), roadEndRoll);
		UE_LOG(LogTemp, Log, TEXT("Magnet spline start roll: %f."), magnetStartRoll);
		UE_LOG(LogTemp, Log, TEXT("Magnet spline end roll: %f."), magnetEndRoll);

		bool roadStartRollSimilarToSpecified = FMath::IsNearlyEqual(roadStartRoll, aRollValue);
		bool roadEndRollSimilarToSpecified = FMath::IsNearlyEqual(roadEndRoll, aRollValue);
		bool magnetStartRollSimilarToSpecified = FMath::IsNearlyEqual(magnetStartRoll, aRollValue);
		bool magnetEndRollSimilarToSpecified = FMath::IsNearlyEqual(magnetEndRoll, aRollValue);

		if (!roadStartRollSimilarToSpecified || !roadEndRollSimilarToSpecified || !magnetStartRollSimilarToSpecified || !magnetEndRollSimilarToSpecified)
		{
			UE_LOG(LogTemp, Log, TEXT("Components don't have roll similar to the specified."));
			return false;
		}
		++index;
	}
	return true;
}

void ATrackGeneratorMOCK::widenSplines(float aWidthValue)
{
	for (auto& trackSection : trackSections)
	{
		trackSection.initialWidth = aWidthValue;
	}
	UE_LOG(LogTemp, Log, TEXT("Width has been set to: %f. Now recreate the spline mesh components."), aWidthValue);
	recreateSplineMeshComponents();
}

bool ATrackGeneratorMOCK::splineMeshComponentsWidthIs(float aWidthValue)
{
	int index = 0;
	for (const auto& trackSection : trackSections)
	{
		float roadInitialWidth = trackSection.roadSpline->GetStartScale().X;
		float roadFinalWidth = trackSection.roadSpline->GetEndScale().X;
		float magnetInitialWidth = trackSection.magnetSpline->GetStartScale().X;
		float magnetFinalWidth = trackSection.magnetSpline->GetEndScale().X;

		UE_LOG(LogTemp, Log, TEXT("Specified width: %f."), aWidthValue);
		UE_LOG(LogTemp, Log, TEXT("Spline point index: %d."), index);
		UE_LOG(LogTemp, Log, TEXT("Road spline initial width: %f."), roadInitialWidth);
		UE_LOG(LogTemp, Log, TEXT("Road spline final width: %f."), roadFinalWidth);
		UE_LOG(LogTemp, Log, TEXT("Magnet spline initial width: %f."), magnetInitialWidth);
		UE_LOG(LogTemp, Log, TEXT("Magnet spline final width: %f."), magnetFinalWidth);

		bool roadInitialScaleSimilarToSpecified = FMath::IsNearlyEqual(roadInitialWidth, aWidthValue);
		bool roadEndScaleSimilarToSpecified = FMath::IsNearlyEqual(roadFinalWidth, aWidthValue);
		bool magnetInitialScaleSimilarToSpecified = FMath::IsNearlyEqual(magnetInitialWidth, aWidthValue);
		bool magnetEndScaleSimilarToSpecified = FMath::IsNearlyEqual(magnetFinalWidth, aWidthValue);

		if (!roadInitialScaleSimilarToSpecified || !roadEndScaleSimilarToSpecified || !magnetInitialScaleSimilarToSpecified || !magnetEndScaleSimilarToSpecified)
		{
			UE_LOG(LogTemp, Log, TEXT("Components don't have width similar to the specified."));
			return false;
		}
		++index;
	}
	return true;
}

void ATrackGeneratorMOCK::disableCollisions()
{
	collisionsEnabled = false;
	recreateSplineMeshComponents();
}

bool ATrackGeneratorMOCK::splineMeshComponentsCollisionsDisabled()
{
	for (const auto& trackSection : trackSections)
	{
		if (trackSection.magnetSpline->GetCollisionEnabled() != ECollisionEnabled::NoCollision || trackSection.roadSpline->GetCollisionEnabled() != ECollisionEnabled::NoCollision)
		{
			UE_LOG(LogTemp, Log, TEXT("Component has collisions enabled when setting it to disable."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::splineMeshComponentsExpectedCollisions()
{
	return collisionEnabledToQueryOnlyOnMagnetSplines() && roadSplinesHaveCollisionEnabledSetToQueryAndPhysics();
}

bool ATrackGeneratorMOCK::boundsSplinesAreAttachedToRoadSplines()
{
	for (const auto& trackSection : trackSections)
	{
		if (!trackSection.roadSpline || !trackSection.boundsSpline)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline or bounds spline is nullptr."));
			return false;
		}
		if (trackSection.boundsSpline->GetAttachParent() != trackSection.roadSpline)
		{
			UE_LOG(LogTemp, Log, TEXT("Bounds spline isn't attached to road spline."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::boundsSplinesMobilitySameAsRoadSplines()
{
	for (const auto& trackSection : trackSections)
	{
		if (!trackSection.roadSpline || !trackSection.boundsSpline)
		{
			UE_LOG(LogTemp, Log, TEXT("Road spline or bounds spline is nullptr."));
			return false;
		}
		if (trackSection.boundsSpline->Mobility != trackSection.roadSpline->Mobility)
		{
			UE_LOG(LogTemp, Log, TEXT("Bounds spline at doesn't have the same mobility as the road spline."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::boundsSplinesAndPointsHaveSameTangents()
{
	int index = 0;
	for (const auto& trackSection : trackSections)
	{
		FVector boundsSplineStartTangent = (trackSection.boundsSpline)->GetStartTangent();
		FVector boundsSplineEndTangent = (trackSection.boundsSpline)->GetEndTangent();
		FVector currentSplinePointTangent = splineComponent->GetTangentAtSplinePoint(index, ESplineCoordinateSpace::Local);
		FVector nextSplinePointTangent = splineComponent->GetTangentAtSplinePoint(nextSplineIndexOf(index), ESplineCoordinateSpace::Local);

		UE_LOG(LogTemp, Log, TEXT("current spline point tangent: %s."), *currentSplinePointTangent.ToString());
		UE_LOG(LogTemp, Log, TEXT("Bounds spline start tangent: %s."), *boundsSplineStartTangent.ToString());
		UE_LOG(LogTemp, Log, TEXT("Next spline point tangent: %s."), *nextSplinePointTangent.ToString());
		UE_LOG(LogTemp, Log, TEXT("Bounds spline end tangent: %s."), *boundsSplineEndTangent.ToString());

		if (!boundsSplineStartTangent.Equals(currentSplinePointTangent) || !boundsSplineEndTangent.Equals(nextSplinePointTangent))
		{
			UE_LOG(LogTemp, Log, TEXT("Bounds spline tangents don't match spline point tangents."));
			return false;
		}
		++index;
	}

	return true;
}

bool ATrackGeneratorMOCK::boundsSplinesHaveMeshesSet()
{
	for (const auto& trackSection : trackSections)
	{
		if (!trackSection.boundsSpline->GetStaticMesh())
		{
			UE_LOG(LogTemp, Log, TEXT("Bounds spline doesn't have static mesh set."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::boundsSplinesAreHiddenInGame()
{
	for (const auto& trackSection : trackSections)
	{
		if (!trackSection.boundsSpline->bHiddenInGame)
		{
			UE_LOG(LogTemp, Log, TEXT("Bounds spline isn't set to be hidden in game."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::boundsSplinesHaveSmoothInterpolation()
{
	for (const auto& trackSection : trackSections)
	{
		if (!trackSection.boundsSpline->bSmoothInterpRollScale)
		{
			UE_LOG(LogTemp, Log, TEXT("Bounds spline doesn't have smooth roll interpolation."));
			return false;
		}
	}
	return true;
}

bool ATrackGeneratorMOCK::boundsSplinesHaveSameRollAs(float aRollValue)
{
	int index = 0;
	for (const auto& trackSection : trackSections)
	{
		float boundsStartRoll = trackSection.boundsSpline->GetStartRoll();
		float boundsEndRoll = trackSection.boundsSpline->GetEndRoll();

		UE_LOG(LogTemp, Log, TEXT("Specified roll: %f."), aRollValue);
		UE_LOG(LogTemp, Log, TEXT("Spline point index: %d."), index);
		UE_LOG(LogTemp, Log, TEXT("Bounds spline start roll: %f."), boundsStartRoll);
		UE_LOG(LogTemp, Log, TEXT("Bounds spline end roll: %f."), boundsEndRoll);

		bool boundsStartRollSimilarToSpecified = FMath::IsNearlyEqual(boundsStartRoll, aRollValue);
		bool boundsEndRollSimilarToSpecified = FMath::IsNearlyEqual(boundsEndRoll, aRollValue);

		if (!boundsStartRollSimilarToSpecified || !boundsEndRollSimilarToSpecified)
		{
			UE_LOG(LogTemp, Log, TEXT("Bounds splines don't have roll similar to the specified."));
			return false;
		}
		++index;
	}
	return true;
}



