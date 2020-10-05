// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackMOCK.h"

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
	return magnetBox? true : false;
}

bool ATrackMOCK::magnetBoxAttachedToRoot()
{
	return magnetBox->GetAttachParent() == RootComponent? true : false;
}

bool ATrackMOCK::magnetBoxHasCollisionsEnabled()
{
	return magnetBox->IsCollisionEnabled();
}
