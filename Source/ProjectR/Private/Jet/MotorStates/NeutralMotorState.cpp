// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/MotorStates/NeutralMotorState.h"

void UNeutralMotorState::activate(UMotorDriveComponent* aMotorDriveComponent)
{
	//it's neutral so it doesn't do anything.
}

FVector UNeutralMotorState::linearAccelerationsGeneratedTo(AJet* aJet)
{
	return FVector(0);
}
