// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "ReversingMotorStateTest.h"
#include "Jet/MotorStates/ReversingMotorState.h"

#include "Tests/AutomationEditorCommon.h"
#include "Commands/ReversingMotorStateTestCommands.h"
#include "Commands/JetTestCommands.h"

bool FUReversingMotorStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UReversingMotorState* testReversing = NewObject<UReversingMotorState>();

	TestNotNull(TEXT("The Reversing motor state shouldn't be null when instantiated"), testReversing);

	return true;
}


bool FUReversingMotorStateActivateReversesMotorDriveTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The motor drive's jet velocity should be negative after a brake (after ticking) from idle."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndActivateReversingMotorState);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetVelocityDecrease(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS