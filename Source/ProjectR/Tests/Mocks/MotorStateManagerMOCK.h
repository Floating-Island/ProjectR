// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Jet/MotorStates/MotorStateManager.h"
#include "MotorStateManagerMOCK.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTR_API AMotorStateManagerMOCK : public AMotorStateManager
{
	GENERATED_BODY()

public:
	UMotorState* currentState();
};
