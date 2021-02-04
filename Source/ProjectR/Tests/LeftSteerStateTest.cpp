// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "LeftSteerStateTest.h"
#include "Jet/SteerStates/LeftSteerState.h"

#include "Tests/AutomationEditorCommon.h"
#include "Commands/CommonPIECommands.h"
#include "Commands/JetTestCommands.h"
#include "Commands/LeftSteerStateTestCommands.h"
#include "Mocks/JetMOCK.h"

bool FULeftSteerStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ULeftSteerState* testState = NewObject<ULeftSteerState>();

	TestNotNull("Shouldn't be null when instantiated.", testState);

	return true;
}


bool FULeftSteerStateActivateTurnsLeftSteeringTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* jetClass = AJetMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(jetClass, FTransform()));
	float desiredSpeed = 10000;
	ADD_LATENT_AUTOMATION_COMMAND(FRetrieveAJetMOCKSetVelocityToDesiredSpeed(desiredSpeed));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningLeftSteerStateAndActivateIt);
	int tickCount = 0;
	int tickLimit = 3;
	FVector location = FVector(0);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSteersLeft(tickCount, tickLimit, location, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS