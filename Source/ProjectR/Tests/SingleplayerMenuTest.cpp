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
	establishTestMessageTo(FString("The singleplayer menu should change the current map when clicking the play button."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSingleplayerMenuClickPlayButtonChangesMap(nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUSingleplayerMenuClickingGoBackButtonRemovesFromViewportTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");
	establishTestMessageTo(FString("The singleplayer menu should be removed from viewport when clicking the go back button."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSingleplayerMenuClickGoBackRemovesFromViewport(nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FUSingleplayerMenuClickingGoBackButtonBringsMainMenuTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");
	establishTestMessageTo(FString("The singleplayer menu should change to the main menu when clicking the go back button."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckSingleplayerMenuClickGoBackBringsMainMenu(nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS