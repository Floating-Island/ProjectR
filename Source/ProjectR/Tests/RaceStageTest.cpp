// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceStageTest.h"


#include "GameMode/RaceStages/RaceStage.h"
#include "Mocks/RaceStageMOCK.h"

#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Utilities/PIESessionUtilities.h"


#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceStageIsntNullWhenInstantiatedTest, "ProjectR.RaceStage Tests.Unit.000: Isn't null when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FARaceStageIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ARaceStage* testRaceStage = NewObject<ARaceStage>();

	TestNotNull(TEXT("The race stage shouldn't be null after instantiating it."), testRaceStage);

	return true;
}






IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceStageNextStageReturnsItselfTest, "ProjectR.RaceStage Tests.Unit.001: nextStage returns itself", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FARaceStageNextStageReturnsItselfTest::RunTest(const FString& Parameters)
{
	ARaceStage* testRaceStage = NewObject<ARaceStage>();

	TestTrue(TEXT("The race stage should return itself when calling nextStage."), testRaceStage->nextStage() == testRaceStage);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnARaceStageCommand);

bool FSpawnARaceStageCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	sessionUtilities.spawnInPIEAnInstanceOf<ARaceStageMOCK>();
	
	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRaceModeSubscribedCommand, FAutomationTestBase*, test);

bool FCheckRaceModeSubscribedCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	ARaceStageMOCK* testRaceStage = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceStageMOCK>();
	if (testRaceStage)
	{
		test->TestTrue(TEXT("Race game mode should be subscribed to the stageEndedEvent."), testRaceStage->raceModeIsSubscribed());
		testWorld->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


//uses a mock.
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceStageSubscribesRaceModeToStageEndedEventTest, "ProjectR.RaceStage Tests.Integration.002: Subscribes the game mode to stageEndedEvent", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FARaceStageSubscribesRaceModeToStageEndedEventTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnARaceStageCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRaceModeSubscribedCommand(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS