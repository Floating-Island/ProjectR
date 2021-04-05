// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Jet/MotorStates/MotorStateManager.h"
#include "MotorStateManagerMOCK.generated.h"


/**
 * 
 */
UCLASS()
class TESTINGMODULE_API AMotorStateManagerMOCK : public AMotorStateManager
{
	GENERATED_BODY()

public:
	UMotorState* currentState();

	template<class aMotorStateType>
	void changeMotorStateTo();

	void setOwningJet(AJet* owner);
};

template <class aMotorStateType>
void AMotorStateManagerMOCK::changeMotorStateTo()
{
	updateStateTo<aMotorStateType>();
}
