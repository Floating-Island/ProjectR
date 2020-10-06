// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Track.h"
#include "TrackMOCK.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API ATrackMOCK : public ATrack
{
	GENERATED_BODY()

public:
 	bool hasAFloor();
	bool floorHasStaticMesh();
	bool hasAMagnetBox();
	bool magnetBoxAttachedToRoot();
	bool magnetBoxHasCollisionsEnabled();
	bool magnetBoxHasCollisionsEnabledToQueryOnly();
	bool magnetBoxOverlapsPawnChannel();
    bool magnetBoxGeneratesOverlapEvents();
	bool magnetBoxHasVolume();
	bool magnetBoxMeshIsHidden();
	bool magnetBoxMeshOnTopOfFloor();
	bool magnetBoxHasXYFloorExtension();
};
