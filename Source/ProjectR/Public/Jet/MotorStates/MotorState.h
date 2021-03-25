// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "MotorState.generated.h"

class AJet;
class UMotorDriveComponent;

UCLASS(Abstract)
class PROJECTR_API UMotorState : public UObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UMotorState();
	virtual void activate(UMotorDriveComponent* aMotorDriveComponent) PURE_VIRTUAL(AMotorState::activate, return; );//I don't like this. It should be =0 instead of a macro...
	virtual FVector linearAccelerationsGeneratedTo(AJet* aJet) PURE_VIRTUAL(AMotorState::linearAccelerationsGeneratedTo, return FVector(0); );//I don't like this. It should be =0 instead of a macro...
};
