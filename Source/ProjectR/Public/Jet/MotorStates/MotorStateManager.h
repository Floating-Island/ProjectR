// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotorStateManager.generated.h"

class AMotorState;

UCLASS()
class PROJECTR_API AMotorStateManager : public AActor
{
	GENERATED_BODY()
	
	
public:	
	// Sets default values for this actor's properties
	AMotorStateManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AMotorState* motorState;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void accelerate();
	void brake();
	void neutralize();
};
