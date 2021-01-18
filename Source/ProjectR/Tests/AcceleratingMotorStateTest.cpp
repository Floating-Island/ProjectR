// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "AcceleratingMotorStateTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Jet/MotorStates/AcceleratingMotorState.h"

#include "Commands/AcceleratingMotorStateTestCommands.h"
#include "Commands/JetTestCommands.h"

bool FAAcceleratingMotorStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AAcceleratingMotorState* testAccelerating = NewObject<AAcceleratingMotorState>();

	TestNotNull(TEXT("The Accelerating motor state shouldn't be null when instantiated"), testAccelerating);
}


bool FAAcceleratingMotorStateIsAcceleratingTest::RunTest(const FString& Parameters)
{
	AAcceleratingMotorState* testAccelerating = NewObject<AAcceleratingMotorState>();

	TestTrue(TEXT("isAccelerating should return true"), testAccelerating->isAccelerating());
}


bool FAAcceleratingMotorStateIsntReversingTest::RunTest(const FString& Parameters)
{
	AAcceleratingMotorState* testAccelerating = NewObject<AAcceleratingMotorState>();

	TestFalse(TEXT("isReversing should return false"), testAccelerating->isReversing());
}


bool FAAcceleratingMotorStateActivateAcceleratesMotorDriveTest::RunTest(const FString& Parameters)
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



#endif //WITH_DEV_AUTOMATION_TESTS