// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "NeutralMotorStateTest.h"
#include "Jet/MotorStates/NeutralMotorState.h"

bool FUNeutralMotorStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UNeutralMotorState* testNeutral = NewObject<UNeutralMotorState>();

	TestNotNull(TEXT("The Neutral motor state shouldn't be null when instantiated"), testNeutral);

	return true;
}


bool FUNeutralMotorStateIsntAcceleratingTest::RunTest(const FString& Parameters)
{
	UNeutralMotorState* testNeutral = NewObject<UNeutralMotorState>();

	TestFalse(TEXT("isAccelerating should return false"), testNeutral->isAccelerating());
	
	return true;
}


bool FUNeutralMotorStateIsntReversingTest::RunTest(const FString& Parameters)
{
	UNeutralMotorState* testNeutral = NewObject<UNeutralMotorState>();

	TestFalse(TEXT("isReversing should return false"), testNeutral->isReversing());
	
	return true;
}


bool FUNeutralMotorStateSupportsNetworkingTest::RunTest(const FString& Parameters)
{
	UNeutralMotorState* testNeutral = NewObject<UNeutralMotorState>();

	TestTrue(TEXT("Should support networking"), testNeutral->IsSupportedForNetworking());
	
	return true;	
}



#endif //WITH_DEV_AUTOMATION_TESTS