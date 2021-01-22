// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/NeutralMotorState.h"

bool UNeutralMotorState::isAccelerating()
{
	return false;
}

bool UNeutralMotorState::isReversing()
{
	return false;
}

void UNeutralMotorState::activate(UMotorDriveComponent* aMotorDriveComponent)
{
	//it's neutral so it doesn't do anything.
}
