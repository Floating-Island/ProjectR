// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Jet/MotorStates/MotorState.h"
#include "NeutralMotorState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API UNeutralMotorState : public UMotorState
{
	GENERATED_BODY()

public:
	virtual void activate(UMotorDriveComponent* aMotorDriveComponent) override;
	virtual FVector linearAccelerationsGeneratedTo(AJet* aJet);
};
