// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Jet.generated.h"



class USpringArmComponent;
class UCameraComponent;
class UAntiGravityComponent;

UCLASS()
class PROJECTR_API AJet : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AJet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float accelerationValue;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float brakeAbsoluteValue;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float topSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float steerForceValue;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* meshComponent;

	//spring arm component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* springArm;

	//camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* camera;

	//anti-gravity system component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UAntiGravityComponent* antiGravitySystem;

	bool velocityAlignmentNeeded;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float currentSpeed();

	float settedTopSpeed();

	void accelerate(float anAccelerationMultiplier = 1.0f);

	float acceleration();

	float brakeValue();

	void brake(float aBrakeMultiplier = 1.0f);

	void steer(float aDirectionMultiplier);

	float steerForce();
};
