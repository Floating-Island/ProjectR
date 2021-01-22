// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/ReversingMotorState.h"
#include "Jet/MotorDriveComponent.h"

bool UReversingMotorState::isAccelerating()
{
	return false;
}

bool UReversingMotorState::isReversing()
{
	return true;
}

void UReversingMotorState::activate(UMotorDriveComponent* aMotorDriveComponent)
{
	aMotorDriveComponent->brake();
}
