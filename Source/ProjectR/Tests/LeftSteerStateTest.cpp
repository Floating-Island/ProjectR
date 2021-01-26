// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "LeftSteerStateTest.h"
#include "Jet/SteerStates/LeftSteerState.h"

bool FULeftSteerStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ULeftSteerState* testState = NewObject<ULeftSteerState>();

	TestNotNull("Shouldn't be null when instantiated.", testState);

	return true;
}


bool FULeftSteerStateSupportsNetworkingTest::RunTest(const FString& Parameters)
{
	ULeftSteerState* testState = NewObject<ULeftSteerState>();

	TestTrue("Should support networking.", testState->IsSupportedForNetworking());

	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS