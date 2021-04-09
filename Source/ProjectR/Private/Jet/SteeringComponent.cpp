// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/SteeringComponent.h"
#include "Jet/Jet.h"


USteeringComponent::USteeringComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	owner = Cast<AJet, AActor>(GetOwner());

	steerRadius = 2000;
	steerMaximumForce = std::numeric_limits<float>::max();
}

void USteeringComponent::BeginPlay()
{
	Super::BeginPlay();
	ownerPrimitiveComponent = Cast<UPrimitiveComponent, UActorComponent>(owner->GetComponentByClass(UPrimitiveComponent::StaticClass()));
}

//to get drift, the velocity alignment should be disabled by a moment (as long as the drifting lasts), maintaining the acceleration of the jet.
void USteeringComponent::steer(float aDirectionMultiplier)
{
	if (aDirectionMultiplier != 0)
	{
		//if reverse, change directionMultiplier sign.
		InReverseInverts(aDirectionMultiplier);

		FVector steeringLocation = ownerPrimitiveComponent->GetSocketLocation(FName("FrontSteeringPoint"));
		float centripetalAcceleration = FMath::Pow(owner->forwardVelocity().Size(), 2) / steerRadius;
		float effectiveCentripetalAcceleration = FMath::Min(centripetalAcceleration, steerMaximumForce);
		FVector steerForce = owner->rightVectorProjectionOnFloor() * aDirectionMultiplier * effectiveCentripetalAcceleration;
		ownerPrimitiveComponent->AddForceAtLocation(steerForce, steeringLocation);

		FVector currentForwardVector = owner->ForwardProjectionOnFloor();
		FVector currentLocation = owner->GetActorLocation();
		FTimerDelegate alignVelocityOnNextTick = FTimerDelegate::CreateUObject(this, &USteeringComponent::alignVelocityFrom, currentForwardVector, currentLocation);
		owner->GetWorldTimerManager().SetTimerForNextTick(alignVelocityOnNextTick);//the steering is applied on next tick, so we need to also align velocity on next tick.
	}
}

void USteeringComponent::InReverseInverts(float& aDirectionMultiplier)
{
	if (owner->goesBackwards())
	{
		aDirectionMultiplier = -aDirectionMultiplier;//invert steering
	}
}

void USteeringComponent::alignVelocityFrom(FVector aPreviousForwardVector, FVector aPreviousLocation)
{
	float mass = ownerPrimitiveComponent->GetMass();
	//I use the kinetic energy formula into the work formula and get the force applied from there (v1 is zero):
	float forceMagnitudeToRecreateVelocity = mass * accelerationMagnitudeToAlignVelocityFrom(aPreviousForwardVector);

	FVector previousBackwardsVector = -aPreviousForwardVector;
	FVector counterForce = previousBackwardsVector * forceMagnitudeToRecreateVelocity;
	ownerPrimitiveComponent->AddForce(counterForce);//we cancel the current velocity.

	FVector alignedForce = owner->ForwardProjectionOnFloor() * forceMagnitudeToRecreateVelocity;
	ownerPrimitiveComponent->AddForce(alignedForce);//we set the aligned velocity.
}

float USteeringComponent::steeringRadius()
{
	return steerRadius;
}

void USteeringComponent::steerLeft()
{
	steer(-1);
}

void USteeringComponent::steerRight()
{
	steer(1);
}

float USteeringComponent::accelerationMagnitudeToAlignVelocityFrom(FVector aPreviousLocation)
{
	FVector const currentForwardVelocity = owner->forwardVelocity();
	FVector const currentLocation = owner->GetActorLocation();

	float const squareVelocityDelta = FMath::Pow(currentForwardVelocity.Size(), 2);
	float const distanceFromTick = (currentLocation - aPreviousLocation).Size();

	//I use the kinetic energy formula into the work formula and get the force applied from there (v1 is zero).
	//I only want the acceleration now so I simply cancel the mass on the formula.
	// W = F * Dx
	// W = (1/2) * m * v^2
	// F * Dx = (1/2) * m * v^2
	// m * a * Dx = (1/2) * m * v^2
	// a * Dx = (1/2) * v^2
	// a = (1/2) * (v^2) / Dx
	// a = (v^2) / (2 * Dx)
	// Dx is distanceFromTick
	// v^2 is squareVelocityDelta
	float const accelerationMagnitudeToRecreateVelocity = squareVelocityDelta / (static_cast<float>((2 * distanceFromTick)));

	return accelerationMagnitudeToRecreateVelocity;
}

float USteeringComponent::maximumAllowedSteeringForce()
{
	return steerMaximumForce;
}

