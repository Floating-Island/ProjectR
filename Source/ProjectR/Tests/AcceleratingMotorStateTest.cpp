// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Jet/MotorStates/AcceleratingMotorState.h"
#if WITH_DEV_AUTOMATION_TESTS


#include "AcceleratingMotorStateTest.h"

bool FAAcceleratingMotorStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AAcceleratingMotorState* testAccelerating = NewObject<AAcceleratingMotorState>();

	TestNotNull(TEXT("The Accelerating motor state shouldn't be null when instantiated"), testAccelerating);
}


#endif //WITH_DEV_AUTOMATION_TESTS