// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS


#include "RaceRunningStageTest.h"
#include "Commands/RaceRunningStageTestCommands.h"

#include "GameMode/RaceStages/RaceRunningStage.h"

#include "Tests/AutomationEditorCommon.h"
#include "Commands/CommonPIECommands.h"
#include "Mocks/RaceRunningStageMOCK.h"



bool FARaceRunningStageIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ARaceRunningStage* testRaceRunningStage = NewObject<ARaceRunningStage>();
	TestNotNull(TEXT("The race running stage shouldn't be null after instantiating it."), testRaceRunningStage);

	return true;
}


bool FARaceRunningStageNextStageSpawnsEndedStageTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARaceRunningCallNextStage);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckEndedStageSpawned(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARaceRunningStageSpawnsEndedStageWhenNoRunningJetsTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARaceRunningCallNextStage);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckEndedStageSpawnedWithNoRunningJets(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARaceRunningStageEnablesJetsInputOnStartTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARaceRunningAndStart);

	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckARaceRunningStartEnablesJetsInput(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARaceRunningStageStartInitiatesRemovalOfAnnouncerUIsTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK"));
	establishTestMessageTo(FString("The RaceRunningStage should start removal of announcer UIs from controllers when calling start."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	UClass* raceStageClass = ARaceRunningStageMOCK::StaticClass();
	ADD_LATENT_AUTOMATION_COMMAND(FSpawnInPIEAnActorOfClass(raceStageClass, FTransform()));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRaceRunningStartsAnnouncerUIsRemoval(true, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS
	