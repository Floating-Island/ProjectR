// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "LanMultiplayerMenuTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Commands/LanMultiplayerMenuTestCommands.h"

#include "UI/LanMultiplayerMenu.h"

bool FULanMultiplayerMenuIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ULanMultiplayerMenu* testLanMultiplayerMenu = NewObject<ULanMultiplayerMenu>();
	TestNotNull(TEXT("The LAN multiplayer menu shouldn't be null after instantiating it."), testLanMultiplayerMenu);

	return true;
}


bool FULanMultiplayerMenuClickingGoBackButtonRemovesFromViewportTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLanMultiplayerMenuClickGoBackRemovesFromViewport(nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FULanMultiplayerMenuClickingGoBackButtonBringsMainMenuTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");
	establishTestMessageTo(FString("The lan multiplayer menu should be bring the main menu to viewport when clicking the go back button."));
	establishTickLimitTo(3);
	
	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLanMultiplayerMenuClickGoBackBringsMainMenu(nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FULanMultiplayerMenuClickingCreateSessionButtonStartsSessionTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");
	establishTestMessageTo(FString("When clicking the create session button the lan multiplayer menu should travel to lobby (after session starts)."));
	establishTickLimitTo(10);
	
	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLanMultiplayerMenuClickCreateSessionBringsLobby(nullptr, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}



#endif //WITH_DEV_AUTOMATION_TESTS
