// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "SingleplayerMenuTest.h"
#include "Commands/SingleplayerMenuTestCommands.h"
#include "Tests/AutomationEditorCommon.h"

#include "UI/SingleplayerMenu.h"

bool FUSingleplayerMenuIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	USingleplayerMenu* testSoloMenu = NewObject<USingleplayerMenu>();
	TestNotNull(TEXT("The singleplayer menu shouldn't be null after instantiating it."), testSoloMenu);

	return true;
}


bool FUSingleplayerMenuClickingPlayButtonChangesMapTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
	
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSingleplayerMenuClickChangesMapCommand(tickCount, tickLimit, nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUSingleplayerMenuClickingGoBackButtonRemovesFromViewportTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
	
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSingleplayerMenuClickGoBackRemovesFromViewportCommand(tickCount, tickLimit, nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUSingleplayerMenuClickingGoBackButtonBringsMainMenuTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
	
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckSingleplayerMenuClickGoBackBringsMainMenuCommand(tickCount, tickLimit, nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS