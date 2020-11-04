// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorDriveComponent.h"

// Sets default values for this component's properties
UMotorDriveComponent::UMotorDriveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	jet = GetOwner();
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
	return forwardVelocity().Size();//speed is calculated as the forward velocity, parallel to floor if any.
}

float UMotorDriveComponent::settedTopSpeed()
{
	return topSpeed;
}

void UMotorDriveComponent::accelerate(float anAccelerationMultiplier)
{
	if (anAccelerationMultiplier > 0 && currentSpeed() < settedTopSpeed() && !FMath::IsNearlyEqual(currentSpeed(), settedTopSpeed(), 1.0f))
	{
		FVector forceToApply = ForwardProjectionOnFloor() * acceleration();
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
		FVector forceToApply = ForwardProjectionOnFloor() * (-brakeValue());//notice the '-' next to brakeValue. Brake value's sign is positive.
		jetPhysicsComponent->AddForce(forceToApply * aBrakeMultiplier, NAME_None, true);
	}
}

bool UMotorDriveComponent::goesForward()
{
	FVector forwardDirection = ForwardProjectionOnFloor();
	return forwardVelocity().GetSignVector().Equals(
		forwardDirection.GetSignVector(), 0.1f);
}

bool UMotorDriveComponent::goesBackwards()
{
	return !goesForward() && currentSpeed() > 0;
}


FVector UMotorDriveComponent::forwardVelocity()
{
	return jetVelocity().ProjectOnTo(ForwardProjectionOnFloor());
}

FVector UMotorDriveComponent::rightVectorProjectionOnFloor()
{
	FHitResult obstacle;
	bool nearFloor = traceToFind(obstacle);
	FVector jetRightVector = jet->GetActorRightVector();

	if (nearFloor)
	{
		return FVector::VectorPlaneProject(jetRightVector, obstacle.Normal);
	}
	else
	{
		return jetRightVector;
	}
}

bool UMotorDriveComponent::traceToFind(FHitResult& obstacle)
{
	FVector jetLocation = jet->GetActorLocation();//should take consideration the actor bounds...
	float rayExtension = 1000;
	FVector rayEnd = -jet->GetActorUpVector() * rayExtension;

	FCollisionQueryParams collisionParameters;
	collisionParameters.AddIgnoredActor(jet);
	collisionParameters.bTraceComplex = false;
	collisionParameters.bReturnPhysicalMaterial = false;

	return  GetWorld()->LineTraceSingleByChannel(obstacle, jetLocation, rayEnd, ECollisionChannel::ECC_Visibility, collisionParameters);
}

FVector UMotorDriveComponent::jetVelocity()
{
	return jet->GetVelocity();
}

FVector UMotorDriveComponent::velocityProjectionOnFloor()
{
	FHitResult obstacle;
	bool nearFloor = traceToFind(obstacle);

	if (nearFloor)
	{
		return FVector::VectorPlaneProject(jetVelocity(), obstacle.Normal);
	}
	else
	{
		return FVector::VectorPlaneProject(jetVelocity(), jet->GetActorUpVector());
	}
}
