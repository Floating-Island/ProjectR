// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "MotorStateManagerTest.h"
#include "Jet/MotorStates/MotorStateManager.h"

#include "Tests/AutomationEditorCommon.h"
#include "Commands/MotorStateManagerTestCommands.h"


bool FAMotorStateManagerIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AMotorStateManager* testManager = NewObject<AMotorStateManager>();

	TestNotNull(TEXT("MotorStateManager shouldn't be null when instantiated"), testManager);
	return true;
}


bool FAMotorStateManagerDefaultStateIsNeutralTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnAMotorStateManager);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerDefaultState(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAMotorStateManagerAccelerateChangesStateToAcceleratingTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnAMotorStateManagerAndAccelerateIt);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerStateChangesToAccelerating(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAMotorStateManagerBrakeChangesStateToReversingTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnAMotorStateManagerAndBrakeIt);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerStateChangesToReversing(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAMotorStateManagerNeutralizeChangesStateToNeutralTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnAMotorStateManagerAndNeutralizeIt);
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerStateChangesToNeutral(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAMotorStateManagerAccelerateKeepsStateIfAlreadyAcceleratingTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnAMotorStateManager);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerAccelerateKeepsStateIfAccelerating(tickCount, tickLimit, nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FAMotorStateManagerBrakeKeepsStateIfAlreadyReversingingTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnAMotorStateManager);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckMotorStateManagerBrakeKeepsStateIfReversing(tickCount, tickLimit, nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}





#endif //WITH_DEV_AUTOMATION_TESTS