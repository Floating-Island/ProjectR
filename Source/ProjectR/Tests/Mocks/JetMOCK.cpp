// Fill out your copyright notice in the Description page of Project Settings.


#include "JetMOCK.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

bool AJetMOCK::hasAStaticMesh()
{
	return (meshComponent) ? true : false;
}

bool AJetMOCK::isMeshTheRootComponent()
{
	return (RootComponent == meshComponent) ? true : false;
}

bool AJetMOCK::hasGravityEnabled()
{
	return meshComponent->IsGravityEnabled();
}

bool AJetMOCK::isAffectingNavigation()
{
	return meshComponent->CanEverAffectNavigation();
}

void AJetMOCK::setCurrentXVelocityTo(float aDesiredSpeed)
{
	FVector newVelocity = FVector(aDesiredSpeed, 0, 0);
	meshComponent->SetPhysicsLinearVelocity(newVelocity);
}

bool AJetMOCK::hasASprinArm()
{
	return springArm ? true : false;
}

bool AJetMOCK::isSpringArmAttachedToRoot()
{
	return  springArm->GetAttachParent() == RootComponent ? true : false;
}

bool AJetMOCK::HasCameraComponent()
{
	return camera ? true : false;
}

bool AJetMOCK::isCameraAttachedToSpringArm()
{
	return camera->GetAttachParent() == springArm ? true : false;
}

bool AJetMOCK::usesAbsoluteRotation()
{
	return springArm->IsUsingAbsoluteRotation();
}

float AJetMOCK::getZVelocity()
{
	return meshComponent->GetComponentVelocity().Z;
}

bool AJetMOCK::generatesOverlapEvents()
{
        return meshComponent->GetGenerateOverlapEvents();
}

bool AJetMOCK::meshCollisionIsPawn()
{
	return meshComponent->GetCollisionObjectType() == ECC_Pawn;
}

bool AJetMOCK::centerOfMassIsLowered()
{
	FVector centerOfMassLocation = centerOfMass();
	return false;
}

FVector AJetMOCK::centerOfMass()
{
	return meshComponent->GetCenterOfMass();
}

//bool AJetMOCK::hasAnAntiGravitySystem()
//{
//	return antiGravitySystem? true : false;
//}
