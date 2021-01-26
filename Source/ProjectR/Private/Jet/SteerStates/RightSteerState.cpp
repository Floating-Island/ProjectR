// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/SteerStates/RightSteerState.h"

void URightSteerState::activate(USteeringComponent* aSteeringComponent)
{
	aSteeringComponent->steerRight();
}
