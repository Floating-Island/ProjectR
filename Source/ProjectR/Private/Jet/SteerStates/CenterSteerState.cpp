// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/SteerStates/CenterSteerState.h"

void UCenterSteerState::activate(USteeringComponent* aSteeringComponent)
{
	
}

FVector UCenterSteerState::angularAccelerationGeneratedTo(AJet* aJet)
{
	return FVector(0);
}
