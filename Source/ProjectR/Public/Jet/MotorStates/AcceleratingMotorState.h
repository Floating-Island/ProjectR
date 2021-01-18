// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Jet/MotorStates/MotorState.h"
#include "AcceleratingMotorState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API AAcceleratingMotorState : public AMotorState
{
	GENERATED_BODY()

public:
	virtual bool isAccelerating() override;
	virtual bool isReversing() override;
};
