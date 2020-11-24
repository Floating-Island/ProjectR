// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "LapManagerTest.h"

#include "LapManager/LapManager.h"
#include "Mocks/LapManagerMOCK.h"
#include "Commands/LapManagerTestCommands.h"
#include "Tests/AutomationEditorCommon.h"


bool FALapManagerIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ALapManager* testLapManager = NewObject<ALapManager>();
	TestNotNull(TEXT("The lap manager shouldn't be null after instantiating it."), testLapManager);

	return true;
}


bool FALapManagerHasJetsListedWhenSpawnedTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerAndJetCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckALapManagerStoresJetsCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FALapManagerJetsHaveInitialLapPhaseAsDefaultPhaseTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerAInitialLapPhaseAndJetCommand);
	int tickCount = 0;
	int tickLimit = 1;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetsInitialLapPhaseCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FALapManagerJetsHaveInitialLapCountSetToOneTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerAInitialLapPhaseAndJetCommand);
	int tickCount = 0;
	int tickLimit = 1;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetsInitialLapCountCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FALapManagerJetOverlappingIntermediateChangesPhaseToItFromInitialTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerInitalAndIntermediateLapPhasesAndJetCommand);
	int tickCount = 0;
	int tickLimit = 1;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetChangeFromInitialToIntermediateCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FALapManagerJetOverlappingFinalChangesPhaseToItFromIntermediateTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerIntermediateAndFinalLapPhasesAndJetCommand);
	int tickCount = 0;
	int tickLimit = 1;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetChangeFromIntermediateToFinalCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FALapManagerJetOverlappingInitialChangesPhaseToItFromFinalTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerInitialAndFinalLapPhasesAndJetCommand);
	int tickCount = 0;
	int tickLimit = 1;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetChangeFromFinalToInitialCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FALapManagerJetOverlappingInitialIncreasesLapCountFromFinalTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerInitialAndFinalLapPhasesAndJetCommand);
	int tickCount = 0;
	int tickLimit = 1;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetLapCountChangeFromFinalToInitialCommand(tickCount, tickLimit, std::numeric_limits<int>::max(), this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS
