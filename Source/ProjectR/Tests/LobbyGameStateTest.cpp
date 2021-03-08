// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "LobbyGameStateTest.h"
#include "GameState/LobbyGameState.h"
#include "Tests/AutomationEditorCommon.h"
#include "Commands/LobbyGameStateTestCommands.h"
#include "Commands/NetworkCommands.h"


bool FALobbyGameStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ALobbyGameState* testState = NewObject<ALobbyGameState>();

	TestNotNull(FString("Isn't null when instantiated"), testState);

	return true;
}


bool FALobbyGameStateClickingReturnGoesToMainMenuTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Development/Maps/lobby"));
	establishTestMessageTo(FString("The LobbyGameState should exist in the lobby map."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	
	
	ADD_LATENT_AUTOMATION_COMMAND(FCheckLobbyGameStateExistsInLobby(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FALobbyGameStateUpdatingSelectedMapUpdatesMapOfLobbyMenuClientTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Development/Maps/lobby"));
	establishTestMessageTo(FString("The lobby game state should update the selected map of client lobby menus when updating its own."));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLobbyGameStateUpdatesClientLobbyMenus(FString("this is a map update"), true, numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}





#endif //WITH_DEV_AUTOMATION_TESTS