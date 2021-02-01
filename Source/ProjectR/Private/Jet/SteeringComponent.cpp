// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/SteeringComponent.h"
#include "Jet/Jet.h"


USteeringComponent::USteeringComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	owner = Cast<AJet, AActor>(GetOwner());

	steerRadius = 2000;
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
		FVector steerForce = owner->rightVectorProjectionOnFloor() * aDirectionMultiplier * centripetalAcceleration;
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
	FVector currentForwardVelocity = owner->forwardVelocity();
	FVector currentLocation = owner->GetActorLocation();

	float mass = ownerPrimitiveComponent->GetMass();
	float squareVelocityDelta = FMath::Pow(currentForwardVelocity.Size(), 2);
	float distanceFromTick = (currentLocation - aPreviousLocation).Size();

	//I use the kinetic energy formula into the work formula and get the force applied from there (v1 is zero):
	float forceMagnitudeToRecreateVelocity = mass * squareVelocityDelta / (static_cast<float>((2 * distanceFromTick)));

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

