// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Jet/MotorStates/MotorState.h"
#include "MixedMotorState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API UMixedMotorState : public UMotorState
{
	GENERATED_BODY()

public:
	virtual void activate(UMotorDriveComponent* aMotorDriveComponent) override;
	virtual FVector linearAccelerationsGeneratedTo(AJet* aJet);
};
