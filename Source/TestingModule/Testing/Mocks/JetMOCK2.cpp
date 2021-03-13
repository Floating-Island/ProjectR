// Fill out your copyright notice in the Description page of Project Settings.


#include "JetMOCK2.h"


#include "Jet/MotorStates/MotorStateManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "SteerStateManagerMOCK.h"

AJetMOCK2::AJetMOCK2()
{
	alwaysCancelGravity = false;
}

void AJetMOCK2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (alwaysCancelGravity)
	{
		float weight = abs(physicsMeshComponent->GetMass() * GetWorld()->GetGravityZ());
		physicsMeshComponent->AddForce(FVector(0, 0, weight));
	}
}

bool AJetMOCK2::hasAPhysicsMesh()
{
	return (physicsMeshComponent) ? true : false;
}

bool AJetMOCK2::isPhysicsMeshTheRootComponent()
{
	return (RootComponent == physicsMeshComponent) ? true : false;
}

bool AJetMOCK2::hasGravityEnabled()
{
	return physicsMeshComponent->IsGravityEnabled();
}

bool AJetMOCK2::isAffectingNavigation()
{
	return physicsMeshComponent->CanEverAffectNavigation();
}

void AJetMOCK2::setCurrentXVelocityTo(float aDesiredSpeed)
{
	FVector newVelocity = FVector(aDesiredSpeed, 0, 0);
	physicsMeshComponent->SetPhysicsLinearVelocity(newVelocity);
}

bool AJetMOCK2::hasASprinArm()
{
	return springArm ? true : false;
}

bool AJetMOCK2::isSpringArmAttachedToRoot()
{
	return  springArm->GetAttachParent() == RootComponent ? true : false;
}

bool AJetMOCK2::HasCameraComponent()
{
	return camera ? true : false;
}

bool AJetMOCK2::isCameraAttachedToSpringArm()
{
	return camera->GetAttachParent() == springArm ? true : false;
}

bool AJetMOCK2::usesAbsoluteRotation()
{
	return springArm->IsUsingAbsoluteRotation();
}

float AJetMOCK2::getZVelocity()
{
	return GetVelocity().Z;
}

bool AJetMOCK2::generatesOverlapEvents()
{
	return physicsMeshComponent->GetGenerateOverlapEvents();
}

bool AJetMOCK2::meshCollisionIsPawn()
{
	return physicsMeshComponent->GetCollisionObjectType() == ECC_Pawn;
}

bool AJetMOCK2::centerOfMassIsLowered()
{
	FVector centerOfMassLocation = centerOfMass();
	return centerOfMassLocation.Z <= centerOfMassHeight;
}

FVector AJetMOCK2::centerOfMass()
{
	return physicsMeshComponent->GetCenterOfMass();
}

void AJetMOCK2::cancelGravityOnEveryTick()
{
	alwaysCancelGravity = true;
}

UMotorDriveComponent* AJetMOCK2::motorDriveComponent()
{
	return motorDriveSystem;
}

void AJetMOCK2::setMotorManagerMOCK()
{
	motorManager->Destroy();
	FActorSpawnParameters spawnParameters = FActorSpawnParameters();
	spawnParameters.Owner = this;
	motorManager = GetWorld()->SpawnActor<AMotorStateManagerMOCK>(spawnParameters);
}

UMotorState* AJetMOCK2::currentMotorState()
{
	AMotorStateManagerMOCK* motorManagerMock = Cast<AMotorStateManagerMOCK, AMotorStateManager>(motorManager);

	return motorManagerMock ? motorManagerMock->currentState() : nullptr;
}

bool AJetMOCK2::hasMotorManagerInstantiated()
{
	return motorManager ? true : false;
}

USteeringComponent* AJetMOCK2::steeringComponent()
{
	return steeringSystem;
}

USteerState* AJetMOCK2::currentSteerState()
{
	ASteerStateManagerMOCK* steerManagerMock = Cast<ASteerStateManagerMOCK, ASteerStateManager>(steerManager);
	
	return steerManagerMock ? steerManagerMock->currentState() : nullptr;
}

void AJetMOCK2::setSteerManagerMOCK()
{
	steerManager->Destroy();
	FActorSpawnParameters spawnParameters = FActorSpawnParameters();
	spawnParameters.Owner = this;
	steerManager = GetWorld()->SpawnActor<ASteerStateManagerMOCK>(spawnParameters);
}

bool AJetMOCK2::hasPhysicsMeshHidden()
{
	return !physicsMeshComponent->IsVisible();
}

bool AJetMOCK2::hasJetModelMeshSet()
{
	return jetModelMeshComponent->GetStaticMesh() ? true : false;
}

bool AJetMOCK2::modelMeshAttachedToPhysicsComponent()
{
	return jetModelMeshComponent->IsAttachedTo(physicsMeshComponent);
}


//bool AJetMOCK2::hasAnAntiGravitySystem()
//{
//	return antiGravitySystem? true : false;
//}
