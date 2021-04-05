// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/ReversingMotorState.h"
#include "Jet/MotorDriveComponent.h"
#include "Jet/Jet.h"

void UReversingMotorState::activate(UMotorDriveComponent* aMotorDriveComponent)
{
	aMotorDriveComponent->brake();
}

FVector UReversingMotorState::linearAccelerationsGeneratedTo(AJet* aJet)
{
	return aJet->brakeValue() * (-1) * aJet->ForwardProjectionOnFloor();
}
