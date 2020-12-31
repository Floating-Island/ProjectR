// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotorState.generated.h"

class UMotorDriveComponent;

UCLASS()
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
	virtual bool isAccelerating() =0;
	virtual bool isReversing() =0;
	virtual void activate(UMotorDriveComponent* aMotorDriveComponent) =0;
};
