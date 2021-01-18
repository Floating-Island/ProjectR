// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/ReversingMotorState.h"

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
	
}
