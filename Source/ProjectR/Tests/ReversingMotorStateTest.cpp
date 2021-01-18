// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "ReversingMotorStateTest.h"
#include "Jet/MotorStates/ReversingMotorState.h"


bool FAReversingMotorStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AReversingMotorState* testReversing = NewObject<AReversingMotorState>();

	TestNotNull(TEXT("The Reversing motor state shouldn't be null when instantiated"), testReversing);

	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS