// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "GameInstance/ProjectRGameInstance.h"

#include "ProjectRGameInstanceTest.h"
#include "Commands/ProjectRGameInstanceTestCommands.h"
#include "Tests/AutomationEditorCommon.h"

bool FUProjectRGameInstanceIsSetAsProjectGameInstanceTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckIsSetAsProjectGameInstance(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUProjectRGameInstanceLoadMainMenuCreatesMainMenuTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckCreatesMainMenu(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUProjectRGameInstanceLoadMainMenuCreatesOnlyOneMainMenuTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckCreatesOneMainMenu(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUProjectRGameInstanceLoadSingleplayerMenuCreatesSingleplayerMenuTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckCreatesSingleplayerMenu(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUProjectRGameInstanceLoadSingleplayerMenuCreatesOnlyOneSingleplayerMenuTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckCreatesOneSingleplayerMenu(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUProjectRGameInstanceLoadMainMenuShowsMouseCursorTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckShowsCursorInMainMenu(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUProjectRGameInstanceLoadSingleplayerMenuShowsMouseCursorTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckShowsCursorInSingleplayerMenu(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUProjectRGameInstanceNecessaryPlayersReturnsAsExpectedTest::RunTest(const FString& Parameters)
{
	UProjectRGameInstance* testInstance = NewObject<UProjectRGameInstance>();
	
	int expectedPlayers = 4;

	testInstance->expectedPlayers(expectedPlayers);

	int necessaryPlayers = testInstance->necessaryPlayers();

	TestTrue(TEXT("necessaryPlayers returns the expected number of players in the game."), necessaryPlayers == expectedPlayers);
	return true;
}


bool FUProjectRGameInstanceNecessaryPlayersOneAsDefaultTest::RunTest(const FString& Parameters)
{
	UProjectRGameInstance* testInstance = NewObject<UProjectRGameInstance>();

	TestTrue(TEXT("necessaryPlayers returns 1 as default."), testInstance->necessaryPlayers() == 1);
	return true;
}










#endif //WITH_DEV_AUTOMATION_TESTS
