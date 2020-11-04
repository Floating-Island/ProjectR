// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MotorDriveComponent.generated.h"

class AJet;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTR_API UMotorDriveComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	AJet* jet;
	UPrimitiveComponent* jetPhysicsComponent;
public:
	// Sets default values for this component's properties
	UMotorDriveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Motor Settings")
		float accelerationValue;

	UPROPERTY(EditAnywhere, Category = "Motor Settings")
		float brakeAbsoluteValue;

	UPROPERTY(EditAnywhere, Category = "Motor Settings")
		float topSpeed;

public:
	float currentSpeed();

	float settedTopSpeed();

	void accelerate(float anAccelerationMultiplier = 1.0f);

	float acceleration();

	float brakeValue();

	void brake(float aBrakeMultiplier = 1.0f);

	bool goesForward();
	
	bool goesBackwards();
};
