// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Jet/MotorStates/MotorState.h"
#include "MotorStateManagerMOCK.h"
#include "Jet/Jet.h"
#include "JetMOCK.generated.h"

class USteerState;
/**
 *
 */
UCLASS()
class TESTINGMODULE_API AJetMOCK : public AJet
{
	GENERATED_BODY()

private:
	bool alwaysCancelGravity;
public:
	AJetMOCK();
	virtual void BeginPlay() override;
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

	std::deque<FMovementData>& retrieveMovementHistory();

	int movementHistoryPrefixedSize();

	void addToHistory(FMovementData aMovement);
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
