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
};