// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "SessionManagerTest.h"
#include "Session/SessionManager.h"


bool FUSessionManagerIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	USessionManager* testManager = NewObject<USessionManager>();

	TestNotNull("Shouldn't be null when instantiated.", testManager);

	return true;
}


bool FUSessionManagerHasTheSessionInterfaceWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	USessionManagerMOCK* testManager = NewObject<USessionManagerMOCK>();

	TestNotNull("Session shouldn't be null when instantiated.", testManager->retrieveSession());

	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS