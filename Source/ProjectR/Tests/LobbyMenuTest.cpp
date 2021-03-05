// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "LobbyMenuTest.h"
#include "UI/LobbyMenu.h"
#include "Tests/AutomationEditorCommon.h"
#include "Commands/LobbyMenuTestCommands.h"
#include "Commands/NetworkCommands.h"


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


bool FULobbyMenuGameStatePlayerArrayQuantityChangeIsUpdatedTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Development/Maps/lobby"));
	establishTestMessageTo(FString("The lobby menu should update its playersConnected when the PlayerArray quantity in GameState changes."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckLobbyMenuUpdatesPlayersConnected(false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FULobbyMenuCollapsesMapSelectorWidgetIfNotAuthorityTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Development/Maps/lobby"));
	establishTestMessageTo(FString("The lobby menu should update its playersConnected when the PlayerArray quantity in GameState changes."));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckClientMapSelectorCollapsed(numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


//bool FULobbyMenuReplicatesSelectedMapToClientsTest::RunTest(const FString& Parameters)
//{
//	establishInitialMapDirectoryTo(FString("/Game/Development/Maps/lobby"));
//	establishTestMessageTo(FString("The lobby menu should update its playersConnected when the PlayerArray quantity in GameState changes."));
//	establishTickLimitTo(10);
//
//	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
//	int32 numberOfPlayers = 2;
//	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;
//
//	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FCheckClientMapSelectedReplicates(FString("this isn't a selected map"), true, numberOfPlayers, this));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
//	return true;
//}


bool FULobbyMenuClickingAMapButtonChangesLobbyGameStateSelectedMapTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Development/Maps/lobby"));
	establishTestMessageTo(FString("The lobby menu should the lobby game state update its map when clicking a map."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckClickingAMapChangesLobbyGameState(FString(), true, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}










#endif //WITH_DEV_AUTOMATION_TESTS