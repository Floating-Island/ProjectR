// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "SteerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API USteerState : public UObject
{
	GENERATED_BODY()

public:
	virtual bool IsSupportedForNetworking() const override;
};
