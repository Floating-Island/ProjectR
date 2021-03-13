// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "RacePlayerStateTest.h"
#include "PlayerState/RacePlayerState.h"
#include "Tests/AutomationEditorCommon.h"
#include "../../Commands/CommonPIECommands.h"
#include "RacePlayerStateTestCommands.h"
#include "../../Commands/NetworkCommands.h"


bool FARacePlayerStateIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ARacePlayerState* testPlayerState = NewObject<ARacePlayerState>();

	TestNotNull(TEXT("Shouldn't be null when instantiated"), testPlayerState);
	
	return true;
}


bool FARacePlayerStateUpdateLapToUpdatesSubscribedRacePlayerUICurrentLapTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-RacePlayerUIContainer"));
	establishTestMessageTo(FString("The race player state should update subscribed racePlayerUIs currentLap when calling updateLapTo."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnGameModeDefaultPawn);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckPlayerStateUpdatesRacePlayerUICurrentLap(nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARacePlayerStateUpdatePositionToUpdatesSubscribedRacePlayerUICurrentPositionTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-RacePlayerUIContainer"));
	establishTestMessageTo(FString("The race player state should update subscribed racePlayerUIs currentPosition when calling updatePositionTo."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnGameModeDefaultPawn);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckPlayerStateUpdatesRacePlayerUICurrentPosition(nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARacePlayerStateServerUpdateLapToUpdatesSubscribedClientRacePlayerUICurrentLapTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-ControllerPlayerState"));
	establishTestMessageTo(FString("The race player state should update subscribed client racePlayerUIs currentLap when calling updateLapTo."));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FCheckServerUpdatesLapReplicatesToClientRaceUI(TArray<ARacePlayerState*>(), numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARacePlayerStateServerUpdatePositionToUpdatesSubscribedClientRacePlayerUICurrentPositionTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-ControllerPlayerState"));
	establishTestMessageTo(FString("The race player state should update subscribed client racePlayerUIs currentPosition when calling updatePositionTo."));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FCheckServerUpdatesPositionReplicatesToClientRaceUI(TArray<ARacePlayerState*>(), numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARacePlayerStateServerSetTotalLapsToSetsSubscribedClientRacePlayerUITotalLapsTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-ControllerPlayerState"));
	establishTestMessageTo(FString("The race player state should update subscribed client racePlayerUIs totalLaps when calling setTotalLaps."));
	establishTickLimitTo(10);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	int32 numberOfPlayers = 2;
	EPlayNetMode networkMode = EPlayNetMode::PIE_ListenServer;

	ADD_LATENT_AUTOMATION_COMMAND(FStartNetworkedPIESession(numberOfPlayers, networkMode));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FCheckServerUpdatesTotalLapsReplicatesToClientRaceUI(TArray<ARacePlayerState*>(), numberOfPlayers, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}






#endif //WITH_DEV_AUTOMATION_TESTS