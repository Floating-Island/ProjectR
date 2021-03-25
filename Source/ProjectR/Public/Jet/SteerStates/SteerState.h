// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Jet/SteeringComponent.h"
#include "SteerState.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECTR_API USteerState : public UObject
{
	GENERATED_BODY()

public:
	virtual void activate(USteeringComponent* aSteeringComponent) PURE_VIRTUAL(USteerState::activate, ; );//I don't like this. It should be =0 instead of a macro...
	virtual FVector angularAccelerationGeneratedTo(AJet* aJet) PURE_VIRTUAL(USteerState::angularAccelerationGeneratedTo, return FVector(0); );//I don't like this. It should be =0 instead of a macro...
};
