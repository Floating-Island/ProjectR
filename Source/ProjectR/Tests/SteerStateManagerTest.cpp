// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "SteerStateManagerTest.h"
#include "Jet/SteerStates/SteerStateManager.h"


bool FASteerStateManagerIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ASteerStateManager* testManager = NewObject<ASteerStateManager>();

	TestNotNull(TEXT("Shouldn't be null when instantiated."), testManager);

	return true;
}


bool FASteerStateManagerDoesntTickTest::RunTest(const FString& Parameters)
{
	ASteerStateManager* testManager = NewObject<ASteerStateManager>();

	TestFalse(TEXT("Shouldn't tick."), testManager->CanEverTick());

	return true;	
}




#endif //WITH_DEV_AUTOMATION_TESTS