// Fill out your copyright notice in the Description page of Project Settings.


#include "JetMOCK.h"


#include "Jet/MotorStates/MotorStateManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AJetMOCK::AJetMOCK()
{
	alwaysSteerRight = false;
	alwaysCancelGravity = false;
	serverSteerAlways = false;
}

void AJetMOCK::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (alwaysSteerRight)
	{
		steer(1);
	}
	if (alwaysCancelGravity)
	{
		float weight = abs(physicsMeshComponent->GetMass() * GetWorld()->GetGravityZ());
		physicsMeshComponent->AddForce(FVector(0, 0, weight));
	}
	if (serverSteerAlways)
	{
		serverSteer(1);
	}
}

bool AJetMOCK::hasAPhysicsMesh()
{
	return (physicsMeshComponent) ? true : false;
}

bool AJetMOCK::isPhysicsMeshTheRootComponent()
{
	return (RootComponent == physicsMeshComponent) ? true : false;
}

bool AJetMOCK::hasGravityEnabled()
{
	return physicsMeshComponent->IsGravityEnabled();
}

bool AJetMOCK::isAffectingNavigation()
{
	return physicsMeshComponent->CanEverAffectNavigation();
}

void AJetMOCK::setCurrentXVelocityTo(float aDesiredSpeed)
{
	FVector newVelocity = FVector(aDesiredSpeed, 0, 0);
	physicsMeshComponent->SetPhysicsLinearVelocity(newVelocity);
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
	return GetVelocity().Z;
}

bool AJetMOCK::generatesOverlapEvents()
{
	return physicsMeshComponent->GetGenerateOverlapEvents();
}

bool AJetMOCK::meshCollisionIsPawn()
{
	return physicsMeshComponent->GetCollisionObjectType() == ECC_Pawn;
}

bool AJetMOCK::centerOfMassIsLowered()
{
	FVector centerOfMassLocation = centerOfMass();
	return centerOfMassLocation.Z <= centerOfMassHeight;
}

FVector AJetMOCK::centerOfMass()
{
	return physicsMeshComponent->GetCenterOfMass();
}

void AJetMOCK::steerRightEveryTick()
{
	alwaysSteerRight = true;
}

void AJetMOCK::cancelGravityOnEveryTick()
{
	alwaysCancelGravity = true;
}

void AJetMOCK::serverAlwaysSteer()
{
	serverSteerAlways = true;
}

UMotorDriveComponent* AJetMOCK::motorDriveComponent()
{
	return motorDriveSystem;
}

void AJetMOCK::setMotorManagerMOCK()
{
	motorManager->Destroy();
	FActorSpawnParameters spawnParameters = FActorSpawnParameters();
	spawnParameters.Owner = this;
	motorManager = GetWorld()->SpawnActor<AMotorStateManagerMOCK>(spawnParameters);
}

UMotorState* AJetMOCK::currentMotorState()
{
	AMotorStateManagerMOCK* motorManagerMock = Cast<AMotorStateManagerMOCK, AMotorStateManager>(motorManager);
	if (motorManagerMock)
	{
		return motorManagerMock->currentState();
	}
	else
	{
		return nullptr;
	}

}

bool AJetMOCK::hasMotorManagerInstantiated()
{
	return motorManager ? true : false;
}

USteeringComponent* AJetMOCK::steeringComponent()
{
	return steeringSystem;
}

//bool AJetMOCK::hasAnAntiGravitySystem()
//{
//	return antiGravitySystem? true : false;
//}
