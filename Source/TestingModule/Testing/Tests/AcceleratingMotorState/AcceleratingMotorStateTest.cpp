// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "AcceleratingMotorStateTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Jet/MotorStates/AcceleratingMotorState.h"

#include "../AcceleratingMotorState/AcceleratingMotorStateTestCommands.h"
#include "../Jet/JetTestCommands.h"

bool FUAcceleratingMotorStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UAcceleratingMotorState* testAccelerating = NewObject<UAcceleratingMotorState>();

	TestNotNull(TEXT("The Accelerating motor state shouldn't be null when instantiated"), testAccelerating);

	return true;
}


bool FUAcceleratingMotorStateActivateAcceleratesMotorDriveTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The motor drive component's Jet X location should increase after an acceleration is added (after ticking)."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	
	
	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndActivateAcceleratingMotorState);
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetLocation(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}








#endif //WITH_DEV_AUTOMATION_TESTS