// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "RacePlayerStateTest.h"
#include "PlayerState/RacePlayerState.h"
#include "Tests/AutomationEditorCommon.h"
#include "Commands/CommonPIECommands.h"
#include "Commands/RacePlayerStateTestCommands.h"


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


bool FARacePlayerStateLoadRaceUIMakesRacePlayerUISynchronizeVariablesTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-RacePlayerState"));
	establishTestMessageTo(FString("The race player state should update subscribed racePlayerUIs currentPosition when calling updatePositionTo."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckPlayerStateLoadsPlayerRaceUISynchronized(nullptr, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}






#endif //WITH_DEV_AUTOMATION_TESTS