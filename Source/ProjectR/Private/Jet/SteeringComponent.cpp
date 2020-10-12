// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/SteeringComponent.h"
#include "Jet/Jet.h"


USteeringComponent::USteeringComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	owner = Cast<AJet, AActor>(GetOwner());
	
	steerForceValue = 200.0f;
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

void USteeringComponent::alignVelocity()
{
	FVector alignedVelocity = owner->GetActorForwardVector().GetSafeNormal() * owner->currentSpeed();
	if (owner->goesBackwards())
	{
		alignedVelocity = -alignedVelocity;//velocity should go backwards then...
	}
	ownerPrimitiveComponent->SetPhysicsLinearVelocity(alignedVelocity);//this should happen after the jet steers (gets it's torque applied)
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
		FVector torqueToApply = FVector(0, 0, aDirectionMultiplier * steerForce());//directionMultiplier is used to steer right or left and to have a range of steering. Should be changed to get the jet normal instead of the Z axis
		ownerPrimitiveComponent->AddTorqueInDegrees(torqueToApply, NAME_None, true);

		owner->GetWorldTimerManager().SetTimerForNextTick(this, &USteeringComponent::alignVelocity);//the torque is applied on next tick, so we need to align velocity on next tick also.
	}
}

float USteeringComponent::steerForce()
{
	return steerForceValue;
}

