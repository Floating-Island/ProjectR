// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/SteerStates/LeftSteerState.h"
#include "Jet/Jet.h"

void ULeftSteerState::activate(USteeringComponent* aSteeringComponent)
{
	aSteeringComponent->steerLeft();
}

void ULeftSteerState::changesMadeTo(AJet* aJet, FVector& aLinearAcceleration, FVector& anAngularAcceleration)
{
	float aDirection = -1;
	aJet->InReverseInverts(aDirection);
	UPrimitiveComponent* ownerPrimitiveComponent = Cast<UPrimitiveComponent, UActorComponent>(aJet->GetComponentByClass(UPrimitiveComponent::StaticClass()));

	FVector steeringLocation = ownerPrimitiveComponent->GetSocketLocation(FName("FrontSteeringPoint"));
	
	float centripetalAcceleration = FMath::Pow(aJet->forwardVelocity().Size(), 2) / aJet->steerRadius();
	FVector steerAcceleration = aJet->rightVectorProjectionOnFloor() * aDirection * centripetalAcceleration;

	aLinearAcceleration = steerAcceleration;
	FVector primitiveComponentCenterOfMass = ownerPrimitiveComponent->GetCenterOfMass();
	anAngularAcceleration = FVector::CrossProduct(steeringLocation - primitiveComponentCenterOfMass, steerAcceleration);
}
