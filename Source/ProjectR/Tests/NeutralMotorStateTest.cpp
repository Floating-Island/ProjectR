// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "NeutralMotorStateTest.h"
#include "Jet/MotorStates/NeutralMotorState.h"

bool FANeutralMotorStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ANeutralMotorState* testNeutral = NewObject<ANeutralMotorState>();

	TestNotNull(TEXT("The Neutral motor state shouldn't be null when instantiated"), testNeutral);

	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS