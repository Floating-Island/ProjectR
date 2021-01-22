// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/AcceleratingMotorState.h"
#include "Jet/MotorDriveComponent.h"

bool UAcceleratingMotorState::isAccelerating()
{
	return true;
}

bool UAcceleratingMotorState::isReversing()
{
	return false;
}

void UAcceleratingMotorState::activate(UMotorDriveComponent* aMotorDriveComponent)
{
	aMotorDriveComponent->accelerate();
}
