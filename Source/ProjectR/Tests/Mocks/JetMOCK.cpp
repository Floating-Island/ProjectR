// Fill out your copyright notice in the Description page of Project Settings.


#include "JetMOCK.h"

bool AJetMOCK::hasAStaticMesh()
{
	return (meshComponent)? true : false;
}

bool AJetMOCK::isMeshTheRootComponent()
{
	return (RootComponent == meshComponent)? true : false;
}

bool AJetMOCK::hasGravityEnabled()
{
	return meshComponent->IsGravityEnabled();
}

bool AJetMOCK::isAffectingNavigation()
{
	return meshComponent->CanEverAffectNavigation();
}

void AJetMOCK::setCurrentSpeedTo(float aDesiredSpeed)
{
	FVector newVelocity = FVector(aDesiredSpeed, 0, 0);
	meshComponent->SetPhysicsLinearVelocity(newVelocity);
}