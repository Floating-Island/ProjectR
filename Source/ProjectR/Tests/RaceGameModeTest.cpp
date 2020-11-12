// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceGameModeTest.h"


#include "GameMode/RaceGameMode.h"
#include "Jet/Jet.h"

#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Utilities/PIESessionUtilities.h"


#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceGameModeIsntNullWhenInstantiatedTest, "ProjectR.RaceGameMode Tests.Unit.000: Isn't null when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FARaceGameModeIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ARaceGameMode* testRaceGameMode = NewObject<ARaceGameMode>();

	TestNotNull(TEXT("The race game mode shouldn't be null after instantiating it."), testRaceGameMode);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRaceGameModeSetCommand, FAutomationTestBase*, test);

bool FCheckRaceGameModeSetCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	ARaceGameMode* testGameMode = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameMode>();
	if (testGameMode)
	{
		test->TestNotNull(TEXT("Race game mode was succesfully set as game mode in the world."), testGameMode);
		return true;
	}
	UE_LOG(LogTemp, Log, TEXT("Race game mode not loaded yet."));
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceGameModeIsAbleToBeSetInAWorldTest, "ProjectR.RaceGameMode Tests.Unit.001: Is able to be set in a world", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FARaceGameModeIsAbleToBeSetInAWorldTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameMode");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRaceGameModeSetCommand(this));

	return true;
}







DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnSomeJetsInRaceModeCommand);

bool FSpawnSomeJetsInRaceModeCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	sessionUtilities.spawnInPIEAnInstanceOf<AJet>();
	sessionUtilities.spawnInPIEAnInstanceOf<AJet>();
	
	return false;
}


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRaceGameModeHasAllJetsCommand, FAutomationTestBase*, test);

bool FCheckRaceGameModeHasAllJetsCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.currentPIEWorld();
	
	ARaceGameMode* testGameMode = Cast<ARaceGameMode, AGameModeBase>(UGameplayStatics::GetGameMode(testWorld));
	if (testGameMode)
	{
		TSet<AJet*> gameModeJets = testGameMode->jetsInPlay();
		TArray<AJet*> worldJets = sessionUtilities.retrieveFromPIEAllInstancesOf<AJet>();
		bool sameNumberOfJetsInGameMode = gameModeJets.Num() == worldJets.Num();
		
		test->TestTrue(TEXT("Race game mode should have the same number of jets than the world."), sameNumberOfJetsInGameMode);
		return true;
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceGameModeHasTheJetsInPlayTest, "ProjectR.RaceGameMode Tests.Unit.002: Has the jets in play", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FARaceGameModeHasTheJetsInPlayTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameMode");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnSomeJetsInRaceModeCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRaceGameModeHasAllJetsCommand(this));

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS