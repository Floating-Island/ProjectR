// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Jet/SteerStates/SteerState.h"
#include "LeftSteerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API ULeftSteerState : public USteerState
{
	GENERATED_BODY()

public:
	virtual void activate(USteeringComponent* aSteeringComponent) override;
	virtual FVector angularAccelerationGeneratedTo(AJet* aJet) override;
};
