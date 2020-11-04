// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorDriveComponent.h"
#include "Jet/Jet.h"

// Sets default values for this component's properties
UMotorDriveComponent::UMotorDriveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	jet = Cast<AJet, AActor>(GetOwner());
	accelerationValue = 5000.0f;
	brakeAbsoluteValue = 5000.0f;
	topSpeed = 1000.0f;
}


// Called when the game starts
void UMotorDriveComponent::BeginPlay()
{
	Super::BeginPlay();
	jetPhysicsComponent = Cast<UPrimitiveComponent, UActorComponent>(jet->GetComponentByClass(UPrimitiveComponent::StaticClass()));
}


// Called every frame
void UMotorDriveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UMotorDriveComponent::currentSpeed()
{
	return jet->forwardVelocity().Size();//speed is calculated as the forward velocity, parallel to floor if any.
}

float UMotorDriveComponent::settedTopSpeed()
{
	return topSpeed;
}

void UMotorDriveComponent::accelerate(float anAccelerationMultiplier)
{
	if (anAccelerationMultiplier > 0 && currentSpeed() < settedTopSpeed() && !FMath::IsNearlyEqual(currentSpeed(), settedTopSpeed(), 1.0f))
	{
		FVector forceToApply = jet->ForwardProjectionOnFloor() * acceleration();
		jetPhysicsComponent->AddForce(forceToApply * anAccelerationMultiplier, NAME_None, true);
	}
}

float UMotorDriveComponent::acceleration()
{
	return accelerationValue;
}

float UMotorDriveComponent::brakeValue()
{
	return brakeAbsoluteValue;
}

void UMotorDriveComponent::brake(float aBrakeMultiplier)
{
	if (aBrakeMultiplier > 0)
	{
		FVector forceToApply = jet->ForwardProjectionOnFloor() * (-brakeValue());//notice the '-' next to brakeValue. Brake value's sign is positive.
		jetPhysicsComponent->AddForce(forceToApply * aBrakeMultiplier, NAME_None, true);
	}
}

bool UMotorDriveComponent::goesForward()
{
	FVector forwardDirection = jet->ForwardProjectionOnFloor();
	return jet->forwardVelocity().GetSignVector().Equals(
		forwardDirection.GetSignVector(), 0.1f);
}

bool UMotorDriveComponent::goesBackwards()
{
	return !goesForward() && currentSpeed() > 0;
}