// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/SteeringComponent.h"
#include "Jet/Jet.h"


USteeringComponent::USteeringComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	owner = Cast<AJet, AActor>(GetOwner());

	steerForceMagnitude = 250000;
}

void USteeringComponent::BeginPlay()
{
	Super::BeginPlay();
	ownerPrimitiveComponent = Cast<UPrimitiveComponent, UActorComponent>(owner->GetComponentByClass(UPrimitiveComponent::StaticClass()));
}

void USteeringComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USteeringComponent::alignVelocityFrom(FVector aPreviousForwardVector, FVector aPreviousLocation)
{
	FVector currentForwardVelocity = owner->GetVelocity().ProjectOnTo(owner->GetActorForwardVector());
	FVector currentLocation = owner->GetActorLocation();

	float mass = ownerPrimitiveComponent->GetMass();
	float squareVelocityDelta = FMath::Pow(currentForwardVelocity.Size(), 2);
	float distanceFromTick = (currentLocation - aPreviousLocation).Size();

	//I use the kinetic energy formula into the work formula and get the force applied from there (v1 is zero):
	float forceMagnitudeToRecreateVelocity = mass * squareVelocityDelta / (static_cast<float>((2 * distanceFromTick)));

	FVector previousBackwardsVector = -aPreviousForwardVector;

	FVector counterForce = previousBackwardsVector * forceMagnitudeToRecreateVelocity;

	ownerPrimitiveComponent->AddForce(counterForce);

	FVector alignedForce = owner->GetActorForwardVector() * forceMagnitudeToRecreateVelocity;
	ownerPrimitiveComponent->AddForce(alignedForce);
}

void USteeringComponent::InReverseInverts(float& aDirectionMultiplier)
{
	if (owner->goesBackwards())
	{
		aDirectionMultiplier = -aDirectionMultiplier;//invert steering
	}
}

//to get drift, the velocity alignment should be disabled by a moment (as long as the drifting lasts), maintaining the acceleration of the jet.
void USteeringComponent::steer(float aDirectionMultiplier)
{
	if (aDirectionMultiplier != 0 && !FMath::IsNearlyZero(owner->currentSpeed(), 0.5f))
	{
		//if reverse, change directionMultiplier sign.
		InReverseInverts(aDirectionMultiplier);
		//replace this with torque?
		FVector steeringLocation = ownerPrimitiveComponent->GetSocketLocation(FName("BackSteeringPoint"));
		FVector steerForce = owner->GetActorRightVector() * -aDirectionMultiplier * steerForceMagnitude;
		ownerPrimitiveComponent->AddForceAtLocation(steerForce, steeringLocation);
		/*FVector torqueToApply = FVector(0, 0, steerForceMagnitude * aDirectionMultiplier);
		ownerPrimitiveComponent->AddTorque(torqueToApply, NAME_None, true);*/
		//and leave this as is:
		FVector currentForwardVector = owner->GetActorForwardVector();
		FVector currentLocation = owner->GetActorLocation();
		FTimerDelegate alignVelocityOnNextTick = FTimerDelegate::CreateUObject(this, &USteeringComponent::alignVelocityFrom, currentForwardVector, currentLocation);
		owner->GetWorldTimerManager().SetTimerForNextTick(alignVelocityOnNextTick);//the torque is applied on next tick, so we need to also align velocity on next tick.
	}
}

float USteeringComponent::steerForce()
{
	return steerForceMagnitude;
}

