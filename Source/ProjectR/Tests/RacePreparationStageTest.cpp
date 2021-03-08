// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "RacePreparationStageTest.h"
#include "Commands/RacePreparationStageTestCommands.h"

#include "GameMode/RaceStages/RacePreparationStage.h"

#include "Tests/AutomationEditorCommon.h"


bool FARacePreparationStageIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ARacePreparationStage* testRacePreparationStage = NewObject<ARacePreparationStage>();
	TestNotNull(TEXT("The race preparation stage shouldn't be null after instantiating it."), testRacePreparationStage);

	return true;
}


bool FARacePreparationStageNextStageSpawnsRaceBeginningStageTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARacePreparationStage(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARacePreparationStagStartSpawnsLapManagerTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARacePreparationMakeItStart);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLapManagerSpawned(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARacePreparationStagStartCreatesNecessaryPlayersTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK"));
	establishTestMessageTo(FString("Race preparation start should generate the remaining necessary players in the game."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FCheckPlayersQuantityOnStart(false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARacePreparationStagStartMakesControllersPossessJetsTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK"));
	establishTestMessageTo(FString("Race preparation start should make the controllers possess the jets."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FCheckPlayersPossessingJets(false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


bool FARacePreparationStagStartDisablesJetsInputTest::RunTest(const FString& Parameters)
{
	establishInitialMapDirectoryTo(FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK"));
	establishTestMessageTo(FString("Race preparation start should disable the jets input."));
	establishTickLimitTo(3);

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(retrieveInitialMapDirectory()));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	
	

	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetsInputDisabled(false, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}





#endif //WITH_DEV_AUTOMATION_TESTS

