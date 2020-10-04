// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/SteeringComponent.h"
#include "Jet/Jet.h"

// Sets default values for this component's properties
USteeringComponent::USteeringComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	owner = Cast<AJet, AActor>(GetOwner());
	
	steerForceValue = 200.0f;
}


// Called when the game starts
void USteeringComponent::BeginPlay()
{
	Super::BeginPlay();
	ownerPrimitiveComponent = Cast<UPrimitiveComponent, UActorComponent>(owner->GetComponentByClass(UPrimitiveComponent::StaticClass()));
}


// Called every frame
void USteeringComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USteeringComponent::alignVelocity()
{
	FVector alignedVelocity = owner->GetActorForwardVector().GetSafeNormal() * owner->currentSpeed();
	if (goesBackwards())
	{
		alignedVelocity = -alignedVelocity;//velocity should go backwards then...
	}
	ownerPrimitiveComponent->SetPhysicsLinearVelocity(alignedVelocity);//this should happen after the jet steers (gets it's torque applied)
}


bool USteeringComponent::goesForward()
{
	FVector forwardDirection = owner->GetActorForwardVector();
	return owner->GetVelocity().ProjectOnTo(forwardDirection).GetSignVector().Equals(
		forwardDirection.GetSignVector(), 0.1f);
}

bool USteeringComponent::goesBackwards()
{
	return !goesForward();
}

void USteeringComponent::InReverseInverts(float& aDirectionMultiplier)
{
	if (goesBackwards())//is going backwards. Should add to it that the jet is actually moving (speed bigger than 0).
	{
		aDirectionMultiplier = -aDirectionMultiplier;//invert steering
	}
}

//to get drift, the velocity alignment should be disabled by a moment (as long as the drifting lasts), maintaining the acceleration of the jet.
void USteeringComponent::steer(float aDirectionMultiplier)
{
	if (aDirectionMultiplier != 0)
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

