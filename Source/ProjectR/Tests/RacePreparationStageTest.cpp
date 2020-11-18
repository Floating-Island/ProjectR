// Fill out your copyright notice in the Description page of Project Settings.


#include "RacePreparationStageTest.h"



#include "../Public/LapManager/LapManager.h"
#include "GameMode/RaceStages/RacePreparationStage.h"
#include "GameMode/RaceStages/RaceBeginningStage.h"

#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Utilities/PIESessionUtilities.h"


#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARacePreparationStageIsntNullWhenInstantiatedTest, "ProjectR.RacePreparationStage Tests.Unit.000: Isn't null when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FARacePreparationStageIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ARacePreparationStage* testRacePreparationStage = NewObject<ARacePreparationStage>();

	TestNotNull(TEXT("The race preparation stage shouldn't be null after instantiating it."), testRacePreparationStage);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FSpawnARacePreparationStageCommand, FAutomationTestBase*, test);

bool FSpawnARacePreparationStageCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	ARacePreparationStage* testPreparation = sessionUtilities.retrieveFromPIEAnInstanceOf<ARacePreparationStage>();
	if(testPreparation == nullptr)
	{
		testPreparation = sessionUtilities.spawnInPIEAnInstanceOf<ARacePreparationStage>();
	}
	ARaceBeginningStage* testBeginning = Cast<ARaceBeginningStage,ARaceStage>(testPreparation->nextStage());

	test->TestNotNull(TEXT("The race preparation stage's nextStage should spawn a race beginning stage in the world."), testBeginning);
	testWorld->bDebugFrameStepExecution = true;
	return true;

}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARacePreparationStageNextStageSpawnsRaceBeginningStageTest, "ProjectR.RacePreparationStage Tests.Unit.001: nextStage spawns a race beginning stage", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FARacePreparationStageNextStageSpawnsRaceBeginningStageTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARacePreparationStageCommand(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnARacePreparationMakeItStartCommand);

bool FSpawnARacePreparationMakeItStartCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	
	ARacePreparationStage* testPreparation = sessionUtilities.spawnInPIEAnInstanceOf<ARacePreparationStage>();

	testPreparation->start();
	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckLapManagerSpawnedCommand, FAutomationTestBase*, test);

bool FCheckLapManagerSpawnedCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	ARacePreparationStage* testPreparation = sessionUtilities.retrieveFromPIEAnInstanceOf<ARacePreparationStage>();
	if (testPreparation)
	{
		ALapManager* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManager>();
		
		test->TestNotNull(TEXT("Race running start should spawn a lap manager."), testManager);
		testWorld->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARacePreparationStagStartSpawnsLapManagerTest, "ProjectR.RacePreparationStage Tests.Unit.002: start spawns a lap manager", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FARacePreparationStagStartSpawnsLapManagerTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARacePreparationMakeItStartCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckLapManagerSpawnedCommand(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS

