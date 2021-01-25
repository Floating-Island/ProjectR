// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/AcceleratingMotorState.h"
#include "Jet/MotorDriveComponent.h"

void UAcceleratingMotorState::activate(UMotorDriveComponent* aMotorDriveComponent)
{
	aMotorDriveComponent->accelerate();
}
