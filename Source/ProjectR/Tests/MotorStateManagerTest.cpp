// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "MotorStateManagerTest.h"
#include "Jet/MotorStates/MotorStateManager.h"


bool FAMotorStateManagerIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AMotorStateManager* testManager = NewObject<AMotorStateManager>();

	TestNotNull(TEXT("MotorStateManager shouldn't be null when instantiated"), testManager);

	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS