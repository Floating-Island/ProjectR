// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceRunningStageTest.h"



#include "../Public/LapManager/LapManager.h"
#include "GameMode/RaceStages/RaceRunningStage.h"
#include "GameMode/RaceStages/RaceEndedStage.h"

#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Utilities/PIESessionUtilities.h"


#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceRunningStageIsntNullWhenInstantiatedTest, "ProjectR.RaceRunningStage Tests.Unit.000: Isn't null when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FARaceRunningStageIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ARaceRunningStage* testRaceRunningStage = NewObject<ARaceRunningStage>();

	TestNotNull(TEXT("The race running stage shouldn't be null after instantiating it."), testRaceRunningStage);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnARaceRunningCallCountdownStartCommand);

bool FSpawnARaceRunningCallCountdownStartCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	
	ARaceRunningStage* testBeginning = sessionUtilities.spawnInPIEAnInstanceOf<ARaceRunningStage>();

	testBeginning->nextStage();
	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckEndedStageSpawnedCommand, FAutomationTestBase*, test);

bool FCheckEndedStageSpawnedCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	ARaceRunningStage* testRunning = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceRunningStage>();
	if (testRunning)
	{
		ARaceEndedStage* testEnded = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceEndedStage>();
		
		test->TestNotNull(TEXT("Race running next stage should spawn a race ended stage."), testEnded);
		testWorld->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceRunningStageNextStageSpawnsEndedStageTest, "ProjectR.RaceRunningStage Tests.Unit.001: nextStage spawns a race ended stage", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FARaceRunningStageNextStageSpawnsEndedStageTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARaceRunningCallCountdownStartCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckEndedStageSpawnedCommand(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS
