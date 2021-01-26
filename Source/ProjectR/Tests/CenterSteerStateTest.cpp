// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "CenterSteerStateTest.h"
#include "Jet/SteerStates/CenterSteerState.h"


bool FUCenterSteerStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UCenterSteerState* testState = NewObject<UCenterSteerState>();

	TestNotNull("Shouldn't be null when instantiated.", testState);

	return true;
}


bool FUCenterSteerStateSupportsNetworkingTest::RunTest(const FString& Parameters)
{
	UCenterSteerState* testState = NewObject<UCenterSteerState>();

	TestTrue("Should support networking.", testState->IsSupportedForNetworking());

	return true;
}





#endif //WITH_DEV_AUTOMATION_TESTS