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


bool FANeutralMotorStateIsntAcceleratingTest::RunTest(const FString& Parameters)
{
	ANeutralMotorState* testNeutral = NewObject<ANeutralMotorState>();

	TestFalse(TEXT("isAccelerating should return false"), testNeutral->isAccelerating());
	
	return true;
}


bool FANeutralMotorStateIsntReversingTest::RunTest(const FString& Parameters)
{
	ANeutralMotorState* testNeutral = NewObject<ANeutralMotorState>();

	TestFalse(TEXT("isReversing should return false"), testNeutral->isReversing());
	
	return true;
}


bool FANeutralMotorStateReplicatesTest::RunTest(const FString& Parameters)
{
	ANeutralMotorState* testNeutral = NewObject<ANeutralMotorState>();

	TestTrue(TEXT("Should have SetReplicates set to true"), testNeutral->GetIsReplicated());
	
	return true;
}


bool FANeutralMotorStateIsAlwaysRelevantTest::RunTest(const FString& Parameters)
{
	ANeutralMotorState* testNeutral = NewObject<ANeutralMotorState>();

	TestTrue(TEXT("Should have bAlwaysRelevant set to true"), testNeutral->bAlwaysRelevant);
	
	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS