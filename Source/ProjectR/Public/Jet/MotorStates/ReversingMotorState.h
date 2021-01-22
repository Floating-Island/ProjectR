// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Jet/MotorStates/MotorState.h"
#include "ReversingMotorState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API UReversingMotorState : public UMotorState
{
	GENERATED_BODY()

public:
	virtual bool isAccelerating() override;
	virtual bool isReversing() override;
	virtual void activate(UMotorDriveComponent* aMotorDriveComponent) override;
};
