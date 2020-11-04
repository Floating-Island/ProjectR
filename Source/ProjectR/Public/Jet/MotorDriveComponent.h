// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MotorDriveComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTR_API UMotorDriveComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	AActor* jet;
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

	bool traceToFind(FHitResult& obstacle);

	FVector jetVelocity();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float currentSpeed();

	float settedTopSpeed();

	void accelerate(float anAccelerationMultiplier = 1.0f);

	float acceleration();

	float brakeValue();

	void brake(float aBrakeMultiplier = 1.0f);

	bool goesForward();
	
	bool goesBackwards();

	FVector ForwardProjectionOnFloor();

	FVector forwardVelocity();

	FVector rightVectorProjectionOnFloor();

	FVector velocityProjectionOnFloor();


};
