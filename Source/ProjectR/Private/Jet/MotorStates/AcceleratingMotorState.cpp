// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/AcceleratingMotorState.h"
#include "Jet/MotorDriveComponent.h"
#include "Jet/Jet.h"

void UAcceleratingMotorState::activate(UMotorDriveComponent* aMotorDriveComponent)
{
	aMotorDriveComponent->accelerate();
}

FVector UAcceleratingMotorState::linearAccelerationsGeneratedTo(AJet* aJet)
{
	if(aJet->currentSpeed() < aJet->settedTopSpeed() && !FMath::IsNearlyEqual(aJet->currentSpeed(), aJet->settedTopSpeed(), 1.0f))
	{
		return aJet->acceleration() * aJet->ForwardProjectionOnFloor();
	}
	return FVector(0);
}
