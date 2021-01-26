// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "RightSteerStateTest.h"
#include "Jet/SteerStates/RightSteerState.h"

bool FURightSteerStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	URightSteerState* testState = NewObject<URightSteerState>();

	TestNotNull("Shouldn't be null when instantiated.", testState);

	return true;
}


bool FURightSteerStateSupportsNetworkingTest::RunTest(const FString& Parameters)
{
	URightSteerState* testState = NewObject<URightSteerState>();

	TestTrue("Should support networking.", testState->IsSupportedForNetworking());

	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS