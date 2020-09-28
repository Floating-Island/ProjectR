// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Jet.h"
#include "JetMOCK.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API AJetMOCK : public AJet
{
	GENERATED_BODY()

public:

	bool hasAStaticMesh();

	bool isMeshTheRootComponent();
		
	bool hasGravityEnabled();

	bool isAffectingNavigation();

	void setCurrentSpeedTo(float aDesiredSpeed);

	bool hasASprinArm();

	bool isSpringArmAttachedToRoot();

	bool HasCameraComponent();
	
	bool isCameraAttachedToSpringArm();

	bool usesAbsoluteRotation();

	bool hasAnAntiGravitySystem();
};
