// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectR/Testing/Mocks/MotorStateManagerMOCK.h"
#include "Jet/Jet.h"
#include "JetMOCK2.generated.h"


class USteerState;
/**
 * 
 */
UCLASS()
class TESTINGMODULE_API AJetMOCK2 : public AJet
{
	GENERATED_BODY()

private:
	bool alwaysCancelGravity;


	public:
	AJetMOCK2();
	virtual void Tick(float DeltaTime) override;

	bool hasAPhysicsMesh();

	bool isPhysicsMeshTheRootComponent();

	bool hasGravityEnabled();

	bool isAffectingNavigation();

	void setCurrentXVelocityTo(float aDesiredSpeed);

	bool hasASprinArm();

	bool isSpringArmAttachedToRoot();

	bool HasCameraComponent();

	bool isCameraAttachedToSpringArm();

	bool usesAbsoluteRotation();

	/*bool hasAnAntiGravitySystem();*/

	float getZVelocity();

    bool generatesOverlapEvents();

	bool meshCollisionIsPawn();

	bool centerOfMassIsLowered();

	FVector centerOfMass();

	void cancelGravityOnEveryTick();

	UMotorDriveComponent* motorDriveComponent();

	void setMotorManagerMOCK();

	UMotorState* currentMotorState();

	template<class aMotorStateType>
	void changeMotorStateTo();

	bool hasMotorManagerInstantiated();

	USteeringComponent* steeringComponent();

	USteerState* currentSteerState();

	void setSteerManagerMOCK();

	bool hasPhysicsMeshHidden();

	bool hasJetModelMeshSet();

	bool modelMeshAttachedToPhysicsComponent();
};


template <class aMotorStateType>
void AJetMOCK2::changeMotorStateTo()
{
	AMotorStateManagerMOCK* motorManagerMock = Cast<AMotorStateManagerMOCK, AMotorStateManager>(motorManager);
	if(motorManagerMock)
	{
		motorManagerMock->changeMotorStateTo<aMotorStateType>();
	}
}