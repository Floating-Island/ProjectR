// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/SteerStates/RightSteerState.h"
#include "Jet/Jet.h"

void URightSteerState::activate(USteeringComponent* aSteeringComponent)
{
	aSteeringComponent->steerRight();
}

FVector URightSteerState::angularAccelerationGeneratedTo(AJet* aJet)
{
	float aDirection = 1;
	aJet->InReverseInverts(aDirection);
	UPrimitiveComponent* ownerPrimitiveComponent = Cast<UPrimitiveComponent, UActorComponent>(aJet->GetComponentByClass(UPrimitiveComponent::StaticClass()));

	FVector steeringLocation = ownerPrimitiveComponent->GetSocketLocation(FName("FrontSteeringPoint")) - ownerPrimitiveComponent->GetComponentLocation();
	//check if substracting the component location changes torque
	float centripetalAcceleration = FMath::Pow(aJet->forwardVelocity().Size(), 2) / aJet->steerRadius();
	FVector steerAcceleration = aJet->rightVectorProjectionOnFloor() * aDirection * centripetalAcceleration;
	return FVector::CrossProduct(steeringLocation, steerAcceleration);
}
