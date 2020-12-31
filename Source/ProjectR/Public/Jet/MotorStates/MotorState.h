// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotorState.generated.h"

class UMotorDriveComponent;

UCLASS(Abstract)
class PROJECTR_API AMotorState : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMotorState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual bool isAccelerating() PURE_VIRTUAL(AMotorState::isAccelerating, return false; );//I don't like this. It should be =0 instead of a macro...
	virtual bool isReversing() PURE_VIRTUAL(AMotorState::isReversing, return false; );//I don't like this. It should be =0 instead of a macro...
	virtual void activate(UMotorDriveComponent* aMotorDriveComponent) PURE_VIRTUAL(AMotorState::activate, ; );//I don't like this. It should be =0 instead of a macro...
};
