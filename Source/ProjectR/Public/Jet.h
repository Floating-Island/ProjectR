// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Jet.generated.h"

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

	float accelerationValue;
	
	float speed;

	float topSpeed;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* meshComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float currentSpeed();

	void accelerate();

	void brake();

	void setTopSpeed(float aMaximumSpeed);

	float settedTopSpeed();
	
	bool hasAStaticMesh();

	bool isMeshTheRootComponent();
	
	bool hasGravityEnabled();

	bool isAffectingNavigation();

	void addAcceleration();

	float acceleration();
};
