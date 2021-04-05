// Fill out your copyright notice in the Description page of Project Settings.


#include "MotorStateManagerMOCK.h"

UMotorState* AMotorStateManagerMOCK::currentState()
{
	return motorState;
}

void AMotorStateManagerMOCK::setOwningJet(AJet* owner)
{
	owningJet = owner;
}
