// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/NeutralMotorState.h"

bool ANeutralMotorState::isAccelerating()
{
	return false;
}

bool ANeutralMotorState::isReversing()
{
	return true;
}

void ANeutralMotorState::activate(UMotorDriveComponent* aMotorDriveComponent)
{
	//it's neutral so it doesn't do anything.
}
