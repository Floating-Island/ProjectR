// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Jet/SteerStates/SteerStateManager.h"
#include "SteerStateManagerMOCK.generated.h"

class USteerState;
/**
 * 
 */
UCLASS()
class PROJECTR_API ASteerStateManagerMOCK : public ASteerStateManager
{
	GENERATED_BODY()

public:
	USteerState* currentState();
};
