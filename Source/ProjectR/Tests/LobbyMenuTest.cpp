// Fill out your copyright notice in the Description page of Project Settings.


#include "Commands/NetworkCommands.h"
#if WITH_DEV_AUTOMATION_TESTS


#include "LobbyMenuTest.h"
#include "UI/LobbyMenu.h"
#include "Tests/AutomationEditorCommon.h"
#include "Commands/LobbyMenuTestCommands.h"

bool FULobbyMenuIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ULobbyMenu* testMenu = NewObject<ULobbyMenu>();

	TestNotNull(TEXT("Shouldn't be null when instantiated."), testMenu);

	return true;
}


bool FULobbyMenuClickingReturnGoesToMainMenuTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The lobby menu should return to the main menu when 'Return to Main Menu' is clicked."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckLobbyMenuClickReturnToMainMenu(nullptr, true, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FULobbyMenuClickingAMapAndStartRaceChangesWorldTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld"));
	establishTestMessageTo(FString("The lobby menu should change the map to the one selected after clicking the startRace button."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckLobbyMenuClickSelectMapAndStartRace(nullptr, true, false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FULobbyMenuIsLoadedInLobbyMapLevelBlueprintTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Development/Maps/lobby"));
	establishTestMessageTo(FString("The lobby menu should be loaded by the level blueprint of the lobby menu."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckLobbyMenuLoadedByLevelBlueprint(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}







#endif //WITH_DEV_AUTOMATION_TESTS