// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceBeginningStageTest.h"


#include "GameMode/RaceStages/RaceBeginningStage.h"
#include "Mocks/RaceBeginningStageMOCK.h"
#include "GameMode/RaceStages/RaceRunningStage.h"

#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Utilities/PIESessionUtilities.h"


#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceBeginningStageIsntNullWhenInstantiatedTest, "ProjectR.RaceBeginningStage Tests.Unit.000: Isn't null when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FARaceBeginningStageIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ARaceBeginningStage* testRaceBeginningStage = NewObject<ARaceBeginningStage>();

	TestNotNull(TEXT("The race beginning stage shouldn't be null after instantiating it."), testRaceBeginningStage);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnARaceBeginningMOCKCommand);

bool FSpawnARaceBeginningMOCKCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	ARaceBeginningStageMOCK* testBeginning = sessionUtilities.spawnInPIEAnInstanceOf<ARaceBeginningStageMOCK>();

	testBeginning->start();
	
	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckTimerActiveCommand, FAutomationTestBase*, test);

bool FCheckTimerActiveCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	ARaceBeginningStageMOCK* testBeginning = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceBeginningStageMOCK>();
	if (testBeginning)
	{
		test->TestTrue(TEXT("Race beginning stage should have its timer active at start."), testBeginning->hasTimerActive());
		testWorld->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


//uses a mock.
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceBeginningStageSubscribesRaceModeToStageEndedEventTest, "ProjectR.RaceBeginningStage Tests.Unit.001: Has its timer active at start", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

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






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnARaceBeginningCallCountdownStartCommand);

bool FSpawnARaceBeginningCallCountdownStartCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	
	ARaceBeginningStage* testBeginning = sessionUtilities.spawnInPIEAnInstanceOf<ARaceBeginningStage>();

	testBeginning->nextStage();
	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRunningStageSpawnedCommand, FAutomationTestBase*, test);

bool FCheckRunningStageSpawnedCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	ARaceBeginningStage* testBeginning = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceBeginningStage>();
	if (testBeginning)
	{
		ARaceRunningStage* testRunning = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceRunningStage>();
		
		test->TestNotNull(TEXT("Race beginning next stage should spawn a race running stage."), testRunning);
		testWorld->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceBeginningStageNextStageSpawnsRunningStageTest, "ProjectR.RaceBeginningStage Tests.Unit.002: nextStage spawns a race running stage", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

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