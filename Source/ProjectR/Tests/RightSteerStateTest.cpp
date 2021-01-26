// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS


#include "RightSteerStateTest.h"
#include "Jet/SteerStates/RightSteerState.h"

#include "Tests/AutomationEditorCommon.h"
#include "Commands/JetTestCommands.h"
#include "Commands/RightSteerStateTestCommands.h"

bool FURightSteerStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	URightSteerState* testState = NewObject<URightSteerState>();

	TestNotNull("Shouldn't be null when instantiated.", testState);

	return true;
}


bool FURightSteerStateSupportsNetworkingTest::RunTest(const FString& Parameters)
{
	URightSteerState* testState = NewObject<URightSteerState>();

	TestTrue("Should support networking.", testState->IsSupportedForNetworking());

	return true;
}


bool FURightSteerStateActivateTurnsRightSteeringTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetSetVelocityToTopSpeed);

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningRightSteerStateAndActivateIt);
	int tickCount = 0;
	int tickLimit = 3;
	FVector location = FVector(0);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSteersRight(tickCount, tickLimit, location, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}





#endif //WITH_DEV_AUTOMATION_TESTS