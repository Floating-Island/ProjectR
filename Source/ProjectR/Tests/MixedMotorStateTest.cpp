// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "MixedMotorStateTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Jet/MotorStates/MixedMotorState.h"


bool FUMixedMotorStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UMixedMotorState* testMixed = NewObject<UMixedMotorState>();

	TestNotNull(TEXT("The Mixed motor state shouldn't be null when instantiated"), testMixed);

	return true;
}







#endif //WITH_DEV_AUTOMATION_TESTS