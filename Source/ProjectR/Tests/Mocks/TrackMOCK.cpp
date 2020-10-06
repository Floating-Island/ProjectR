// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackMOCK.h"
#include "Engine/EngineTypes.h"

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

bool ATrackMOCK::magnetBoxHasStaticMesh()
{
	return magnetBox->GetStaticMesh() ? true : false;
}

bool ATrackMOCK::magnetBoxMeshIsHidden()
{
	return magnetBox->bHiddenInGame;
}

bool ATrackMOCK::magnetBoxMeshOnTopOfFloor()
{
	float magnetBoxMeshZLowerBound = magnetBox->GetRelativeLocation().Z - abs(magnetBox->GetStaticMesh()->NegativeBoundsExtension.Z);
	return floorComponent->GetStaticMesh()->PositiveBoundsExtension.Z == magnetBoxMeshZLowerBound;
}
