// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Jet/SteerStates/SteerStateManager.h"
#if WITH_DEV_AUTOMATION_TESTS


#include "SteerStateManagerTest.h"


bool FASteerStateManagerIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ASteerStateManager* testManager = NewObject<ASteerStateManager>();

	TestNotNull(TEXT("Shouldn't be null when instantiated."), testManager);

	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS