// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "RaceBeginningStageTest.h"
#include "Commands/RaceBeginningStageTestCommands.h"

#include "GameMode/RaceStages/RaceBeginningStage.h"

#include "Tests/AutomationEditorCommon.h"



bool FARaceBeginningStageIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ARaceBeginningStage* testRaceBeginningStage = NewObject<ARaceBeginningStage>();
	TestNotNull(TEXT("The race beginning stage shouldn't be null after instantiating it."), testRaceBeginningStage);

	return true;
}


bool FARaceBeginningStageSubscribesRaceModeToStageEndedEventTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARaceBeginningMOCKCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckTimerActiveCommand(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARaceBeginningStageNextStageSpawnsRunningStageTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARaceBeginningCallCountdownStartCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRunningStageSpawnedCommand(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}








#endif //WITH_DEV_AUTOMATION_TESTS