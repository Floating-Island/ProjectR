// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Jet.generated.h"



class USpringArmComponent;
class UCameraComponent;
class UAntiGravityComponent;
class USteeringComponent;
class UMotorDriveComponent;

UCLASS()
class PROJECTR_API AJet : public APawn
{
	GENERATED_BODY()

public:
	AJet();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* physicsMeshComponent;

	//spring arm component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* springArm;

	//camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* camera;

	//anti-gravity system component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UAntiGravityComponent* antiGravitySystem;

	//steering system component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USteeringComponent* steeringSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float centerOfMassHeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UMotorDriveComponent* motorDriveSystem;
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float currentSpeed();

	float settedTopSpeed();

	void accelerate(float anAccelerationMultiplier = 1.0f);

	float acceleration();

	float brakeValue();

	void brake(float aBrakeMultiplier = 1.0f);

	bool goesForward();
	bool goesBackwards();

	float steerRadius();
	void steer(float aDirectionMultiplier);

	float antiGravityHeight();

	FVector ForwardProjectionOnFloor();

	bool traceToFind(FHitResult& obstacle);

	FVector forwardVelocity();

	FVector velocityProjectionOnFloor();

	FVector rightVectorProjectionOnFloor();
};
