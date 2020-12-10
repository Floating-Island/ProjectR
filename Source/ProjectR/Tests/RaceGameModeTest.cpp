// Fill out your copyright notice in the Description page of Project Settings.





#if WITH_DEV_AUTOMATION_TESTS

#include "RaceGameModeTest.h"
#include "GameMode/RaceGameMode.h"
#include "Commands/RaceGameModeTestCommands.h"

#include "Tests/AutomationEditorCommon.h"


bool FARaceGameModeIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ARaceGameMode* testRaceGameMode = NewObject<ARaceGameMode>();
	TestNotNull(TEXT("The race game mode shouldn't be null after instantiating it."), testRaceGameMode);

	return true;
}


bool FARaceGameModeIsAbleToBeSetInAWorldTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameMode");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRaceGameModeSetCommand(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARaceGameModeCreatesExpectedNumberOfJetsTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameMode");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	int tickCount = 0;
	int tickLimit = 2;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckRaceGameModeCreatesAllJetsCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARaceGameModePositionsJetsBehindTheInitialLapPhaseTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameMode");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	int tickCount = 0;
	int tickLimit = 2;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckRaceGameModeJetsPositioningCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARaceGameModeUpdateStageBringsNextStageTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRaceGameModeUpdateStageCommand(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARaceGameModePositionNumberLowerThanTheOneBehindTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnAJetBehindAnotherCommand(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARaceGameModeMovesFinalistsJetsTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnAJetOnFinalLapMakeItFinishCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetMovedToFinalistJets(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARaceGameModePlayersToCreateCreatesThatNumberOfPlayersTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckCreatesTheExpectedPlayers(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARaceGameModeCreatesTheNecessaryGamePlayersTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckCreatesTheNecessaryPlayers(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS
