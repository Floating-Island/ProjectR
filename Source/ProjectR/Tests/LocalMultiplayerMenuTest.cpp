// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "LocalMultiplayerMenuTest.h"
#include "Commands/LocalMultiplayerMenuTestCommands.h"
#include "UI/LocalMultiplayerMenu.h"
#include "Tests/AutomationEditorCommon.h"


bool FULocalMultiplayerMenuIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ULocalMultiplayerMenu* testMenu = NewObject<ULocalMultiplayerMenu>();
	TestNotNull(TEXT("The splitscreen menu shouldn't be null after instantiating it."), testMenu);

	return true;
}


bool FULocalMultiplayerMenuClickingGoBackButtonRemovesFromViewportTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckLocalMultiplayerMenuClickGoBackRemovesFromViewportCommand(tickCount, tickLimit, nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FULocalMultiplayerMenuClickingGoBackButtonBringsMainMenuTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckLocalMultiplayerMenuClickGoBackBringsMainMenuCommand(tickCount, tickLimit, nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FULocalMultiplayerMenuClickingPlayButtonSetsPlayerQuantityTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	int tickCount = 0;
	int tickLimit = 3;
	int numberOfPlayers = 0;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckLocalMultiplayerMenuClickPlaySetsPlayers(tickCount, tickLimit, nullptr, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS