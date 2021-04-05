// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/MixedMotorState.h"
#include "Jet/MotorDriveComponent.h"
#include "Jet/Jet.h"

void UMixedMotorState::activate(UMotorDriveComponent* aMotorDriveComponent)
{
	aMotorDriveComponent->accelerate();
	aMotorDriveComponent->brake();
}

FVector UMixedMotorState::linearAccelerationsGeneratedTo(AJet* aJet)
{
	if(aJet->currentSpeed() < aJet->settedTopSpeed() && !FMath::IsNearlyEqual(aJet->currentSpeed(), aJet->settedTopSpeed(), 1.0f))
	{
		return (aJet->acceleration() - aJet->brakeValue()) * aJet->ForwardProjectionOnFloor();
	}
	return FVector(0);
}
