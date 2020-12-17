// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "RaceRunningStageTest.h"
#include "Commands/RaceRunningStageTestCommands.h"

#include "GameMode/RaceStages/RaceRunningStage.h"

#include "Tests/AutomationEditorCommon.h"



bool FARaceRunningStageIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ARaceRunningStage* testRaceRunningStage = NewObject<ARaceRunningStage>();
	TestNotNull(TEXT("The race running stage shouldn't be null after instantiating it."), testRaceRunningStage);

	return true;
}


bool FARaceRunningStageNextStageSpawnsEndedStageTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARaceRunningCallNextStage);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckEndedStageSpawned(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARaceRunningStageSpawnsEndedStageWhenNoRunningJetsTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARaceRunning);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckEndedStageSpawnedWithNoRunningJets(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARaceRunningStageEnablesJetsInputOnStartTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARaceRunningAndStart);

	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckARaceRunningStartEnablesJetsInput(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS
