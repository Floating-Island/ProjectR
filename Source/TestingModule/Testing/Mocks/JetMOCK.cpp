// Fill out your copyright notice in the Description page of Project Settings.


#include "JetMOCK.h"


#include "Jet/MotorStates/MotorStateManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "SteerStateManagerMOCK.h"

AJetMOCK::AJetMOCK()
{
	alwaysCancelGravity = false;
}

void AJetMOCK::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (alwaysCancelGravity)
	{
		float weight = abs(physicsMeshComponent->GetMass() * GetWorld()->GetGravityZ());
		physicsMeshComponent->AddForce(FVector(0, 0, weight));
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

void AJetMOCK::cancelGravityOnEveryTick()
{
	alwaysCancelGravity = true;
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

	return motorManagerMock ? motorManagerMock->currentState() : nullptr;
}

bool AJetMOCK::hasMotorManagerInstantiated()
{
	return motorManager ? true : false;
}

USteeringComponent* AJetMOCK::steeringComponent()
{
	return steeringSystem;
}

USteerState* AJetMOCK::currentSteerState()
{
	ASteerStateManagerMOCK* steerManagerMock = Cast<ASteerStateManagerMOCK, ASteerStateManager>(steerManager);
	
	return steerManagerMock ? steerManagerMock->currentState() : nullptr;
}

void AJetMOCK::setSteerManagerMOCK()
{
	steerManager->Destroy();
	FActorSpawnParameters spawnParameters = FActorSpawnParameters();
	spawnParameters.Owner = this;
	steerManager = GetWorld()->SpawnActor<ASteerStateManagerMOCK>(spawnParameters);
}

bool AJetMOCK::hasPhysicsMeshHidden()
{
	return !physicsMeshComponent->IsVisible();
}

bool AJetMOCK::hasJetModelMeshSet()
{
	return jetModelMeshComponent->GetStaticMesh() ? true : false;
}

bool AJetMOCK::modelMeshAttachedToPhysicsComponent()
{
	return jetModelMeshComponent->IsAttachedTo(physicsMeshComponent);
}

TArray<FMovementData>& AJetMOCK::retrieveMovementHistory()
{
	return movementHistory;
}

int AJetMOCK::movementHistoryPrefixedSize()
{
	return movementHistorySize;
}

void AJetMOCK::addToHistory(FMovementData aMovement)
{
	addToMovementHistory(aMovement);
}


//bool AJetMOCK::hasAnAntiGravitySystem()
//{
//	return antiGravitySystem? true : false;
//}
