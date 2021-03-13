// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Track/TrackManager.h"
#include "TrackManagerMOCK.generated.h"

/**
 *
 */
UCLASS()
class TESTINGMODULE_API ATrackManagerMOCK : public ATrackManager
{
	GENERATED_BODY()

public:
	TSet<ATrackGenerator*> trackGenerators();
};
