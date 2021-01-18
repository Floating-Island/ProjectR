// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/AcceleratingMotorState.h"
#include "Jet/MotorDriveComponent.h"

bool AAcceleratingMotorState::isAccelerating()
{
	return true;
}

bool AAcceleratingMotorState::isReversing()
{
	return false;
}

void AAcceleratingMotorState::activate(UMotorDriveComponent* aMotorDriveComponent)
{
	aMotorDriveComponent->accelerate();
}
