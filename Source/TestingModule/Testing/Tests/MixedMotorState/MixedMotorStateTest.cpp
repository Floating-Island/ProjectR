// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "MixedMotorStateTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Jet/MotorStates/MixedMotorState.h"

#include "MixedMotorStateTestCommands.h"

bool FUMixedMotorStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	UMixedMotorState* testMixed = NewObject<UMixedMotorState>();

	TestNotNull(TEXT("The Mixed motor state shouldn't be null when instantiated."), testMixed);

	return true;
}


bool FUMixedMotorStateActivateAcceleratesMotorDriveTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("Activating the mixed state should accelerate and brake the jet."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndActivateMixedMotorState);

	float previousSpeed = 0;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMixedStateActivation(previousSpeed, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}









#endif //WITH_DEV_AUTOMATION_TESTS