// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/MixedMotorState.h"
#include "Jet/MotorDriveComponent.h"

void UMixedMotorState::activate(UMotorDriveComponent* aMotorDriveComponent)
{
	aMotorDriveComponent->accelerate();
	aMotorDriveComponent->brake();
}
