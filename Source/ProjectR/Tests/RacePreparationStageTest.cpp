// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "RacePreparationStageTest.h"
#include "Commands/RacePreparationStageTestCommands.h"

#include "GameMode/RaceStages/RacePreparationStage.h"

#include "Tests/AutomationEditorCommon.h"


bool FARacePreparationStageIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ARacePreparationStage* testRacePreparationStage = NewObject<ARacePreparationStage>();
	TestNotNull(TEXT("The race preparation stage shouldn't be null after instantiating it."), testRacePreparationStage);

	return true;
}


bool FARacePreparationStageNextStageSpawnsRaceBeginningStageTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARacePreparationStageCommand(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARacePreparationStagStartSpawnsLapManagerTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARacePreparationMakeItStartCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLapManagerSpawnedCommand(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARacePreparationStagStartCreatesNecessaryPlayersTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckPlayersQuantityOnStartCommand(tickCount, tickLimit, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARacePreparationStagStartMakesControllersPossessJetsTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckPlayersPossessingJets(tickCount, tickLimit, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS

