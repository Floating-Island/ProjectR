// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "AcceleratingMotorStateTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Jet/MotorStates/AcceleratingMotorState.h"

#include "Commands/AcceleratingMotorStateTestCommands.h"
#include "Commands/JetTestCommands.h"

bool FUAcceleratingMotorStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UAcceleratingMotorState* testAccelerating = NewObject<UAcceleratingMotorState>();

	TestNotNull(TEXT("The Accelerating motor state shouldn't be null when instantiated"), testAccelerating);

	return true;
}


bool FUAcceleratingMotorStateActivateAcceleratesMotorDriveTest::RunTest(const FString& Parameters)
{
	
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndActivateAcceleratingMotorState);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetLocation(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUAcceleratingMotorStateSupportsNetworkingTest::RunTest(const FString& Parameters)
{
	UAcceleratingMotorState* testAccelerating = NewObject<UAcceleratingMotorState>();

	TestTrue(TEXT("Should support networking"), testAccelerating->IsSupportedForNetworking());
	
	return true;
}








#endif //WITH_DEV_AUTOMATION_TESTS