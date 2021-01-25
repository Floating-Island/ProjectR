// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "MixedMotorStateTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Jet/MotorStates/MixedMotorState.h"

#include "Commands/MixedMotorStateTestCommands.h"

bool FUMixedMotorStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UMixedMotorState* testMixed = NewObject<UMixedMotorState>();

	TestNotNull(TEXT("The Mixed motor state shouldn't be null when instantiated."), testMixed);

	return true;
}


bool FUMixedMotorStateActivateAcceleratesMotorDriveTest::RunTest(const FString& Parameters)
{
	
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndActivateMixedMotorState);
	int tickCount = 0;
	int tickLimit = 3;
	float previousSpeed = 0;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMixedStateActivation(tickCount, tickLimit, previousSpeed, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUMixedMotorStateSupportsNetworkingTest::RunTest(const FString& Parameters)
{
	UMixedMotorState* testMixed = NewObject<UMixedMotorState>();

	TestTrue(TEXT("The Mixed motor state should support networking."), testMixed->IsSupportedForNetworking());

	return true;
}









#endif //WITH_DEV_AUTOMATION_TESTS