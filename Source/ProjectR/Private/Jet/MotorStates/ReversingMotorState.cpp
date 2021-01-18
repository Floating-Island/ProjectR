// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/ReversingMotorState.h"
#include "Jet/MotorDriveComponent.h"

bool AReversingMotorState::isAccelerating()
{
	return false;
}

bool AReversingMotorState::isReversing()
{
	return true;
}

void AReversingMotorState::activate(UMotorDriveComponent* aMotorDriveComponent)
{
	aMotorDriveComponent->brake();
}
