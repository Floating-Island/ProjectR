// Fill out your copyright notice in the Description page of Project Settings.


#include "JetMOCK.h"

void AJetMOCK::setCurrentSpeedTo(float aDesiredSpeed)
{
	FVector newVelocity = FVector(aDesiredSpeed, 0, 0);
	meshComponent->SetPhysicsLinearVelocity(newVelocity);
}

bool AJetMOCK::hasGravityEnabled()
{
	return meshComponent->IsGravityEnabled();
}

bool AJetMOCK::isAffectingNavigation()
{
	return meshComponent->CanEverAffectNavigation();
}