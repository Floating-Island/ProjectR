// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "RaceBeginningStageTest.h"
#include "RaceBeginningStageTestCommands.h"

#include "GameMode/RaceStages/RaceBeginningStage.h"

#include "Tests/AutomationEditorCommon.h"
#include "../../Commands/CommonPIECommands.h"
#include "../../Mocks/RaceBeginningStageMOCK.h"



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

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARaceBeginningMOCK);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckTimerActive(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARaceBeginningStageNextStageSpawnsRunningStageTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARaceBeginningCallCountdownStart);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRunningStageSpawned(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARaceBeginningStageLoadsAnnouncerUIOnStartTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK"));
	establishTestMessageTo(FString("The RaceBeginningStage should load announcerUI on each controller when calling start."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
	
	
	

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARaceBeginningMOCK);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRaceBeginningStageLoadsAnnouncerUIs(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARaceBeginningStageCountdownToStartModifiesGameStateAnnouncerTextTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK"));
	establishTestMessageTo(FString("The RaceBeginningStage should modify announcerText from game state when calling countdownToStart."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
	
	
	

	UClass* raceStageClass = ARaceBeginningStageMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(raceStageClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRaceBeginningStageCountdownToStartModifiesAnnouncerText(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}









#endif //WITH_DEV_AUTOMATION_TESTS