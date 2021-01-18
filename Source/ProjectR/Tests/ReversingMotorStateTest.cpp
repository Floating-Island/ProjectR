// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "ReversingMotorStateTest.h"
#include "Jet/MotorStates/ReversingMotorState.h"

#include "Tests/AutomationEditorCommon.h"
#include "Commands/ReversingMotorStateTestCommands.h"
#include "Commands/JetTestCommands.h"

bool FAReversingMotorStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AReversingMotorState* testReversing = NewObject<AReversingMotorState>();

	TestNotNull(TEXT("The Reversing motor state shouldn't be null when instantiated"), testReversing);

	return true;
}


bool FAReversingMotorStateIsntAcceleratingTest::RunTest(const FString& Parameters)
{
	AReversingMotorState* testReversing = NewObject<AReversingMotorState>();

	TestFalse(TEXT("isAccelerating should return false"), testReversing->isAccelerating());
	
	return true;
}


bool FAReversingMotorStateIsReversingTest::RunTest(const FString& Parameters)
{
	AReversingMotorState* testReversing = NewObject<AReversingMotorState>();

	TestTrue(TEXT("isReversing should return true"), testReversing->isReversing());
	
	return true;
}


bool FAReversingMotorStateActivateReversesMotorDriveTest::RunTest(const FString& Parameters)
{
	
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndActivateReversingMotorState);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetVelocityDecrease(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS