// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackMOCK.h"
#include "Engine/EngineTypes.h"
#include "Components/BoxComponent.h"

bool ATrackMOCK::hasAFloor()
{
	return floorComponent ? true : false;
}

bool ATrackMOCK::floorHasStaticMesh()
{
	return floorComponent->GetStaticMesh() ? true : false;
}

bool ATrackMOCK::hasAMagnetBox()
{
	return magnetBox ? true : false;
}

bool ATrackMOCK::magnetBoxAttachedToRoot()
{
	return magnetBox->GetAttachParent() == RootComponent ? true : false;
}

bool ATrackMOCK::magnetBoxHasCollisionsEnabled()
{
	return magnetBox->IsCollisionEnabled();
}

bool ATrackMOCK::magnetBoxHasCollisionsEnabledToQueryOnly()
{
	return magnetBox->GetCollisionEnabled() == ECollisionEnabled::QueryOnly ? true : false;
}

bool ATrackMOCK::magnetBoxOverlapsPawnChannel()
{
	return magnetBox->GetCollisionResponseToChannels().GetResponse(ECC_Pawn) == ECR_Overlap;
}

bool ATrackMOCK::magnetBoxGeneratesOverlapEvents()
{
	return magnetBox->GetGenerateOverlapEvents();
}

bool ATrackMOCK::magnetBoxHasVolume()
{
	return (magnetBox->GetScaledBoxExtent().Size > 0) ? true : false;
}

bool ATrackMOCK::magnetBoxMeshIsHidden()
{
	return magnetBox->bHiddenInGame;
}

bool ATrackMOCK::magnetBoxMeshOnTopOfFloor()
{
	float magnetBoxMeshZLowerBound = magnetBox->GetRelativeLocation().Z;
	return FMath::IsNearlyEqual(magnetBox->GetUnscaledBoxExtent().Z, magnetBoxMeshZLowerBound);
}

//bool ATrackMOCK::magnetBoxMeshHasXYFloorExtension()
//{
//	return magnetBox->GetStaticMesh()->PositiveBoundsExtension.X == floorComponent->GetStaticMesh()->PositiveBoundsExtension.X &&
//		magnetBox->GetStaticMesh()->PositiveBoundsExtension.Y == floorComponent->GetStaticMesh()->PositiveBoundsExtension.Y &&
//		magnetBox->GetStaticMesh()->NegativeBoundsExtension.X == floorComponent->GetStaticMesh()->NegativeBoundsExtension.X &&
//		magnetBox->GetStaticMesh()->NegativeBoundsExtension.X == floorComponent->GetStaticMesh()->NegativeBoundsExtension.X;
//}
