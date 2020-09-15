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
	void setCurrentSpeedTo(float aDesiredSpeed);

		
	bool hasGravityEnabled();

	bool isAffectingNavigation();
};
