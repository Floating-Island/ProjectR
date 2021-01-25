// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../../Public/Jet/MotorStates/MotorState.h"
#include "Jet/Jet.h"
#include "JetMOCK.generated.h"

/**
 *
 */
UCLASS()
class PROJECTR_API AJetMOCK : public AJet
{
	GENERATED_BODY()

private:
	bool alwaysSteerRight;
	bool alwaysCancelGravity;
	bool serverSteerAlways;
public:
	AJetMOCK();
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

	void steerRightEveryTick();
	void cancelGravityOnEveryTick();

	void serverAlwaysSteer();

	UMotorDriveComponent* motorDriveComponent();

	void setMotorManagerMOCK();

	UMotorState* currentMotorState();

	template<class aMotorStateType>
	void changeMotorStateTo();
	
};

template <class aMotorStateType>
void AJetMOCK::changeMotorStateTo()
{
	AMotorStateManagerMOCK* motorManagerMock = Cast<AMotorStateManagerMOCK, AMotorStateManager>(motorManager);
	if(motorManagerMock)
	{
		motorManagerMock->changeMotorStateTo<aMotorStateType>();
	}
}
