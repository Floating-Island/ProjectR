// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceGameModeTest.h"


#include "GameMode/RaceGameMode.h"

#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Kismet/GameplayStatics.h"


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








DEFINE_LATENT_AUTOMATION_COMMAND(FSetRaceGameModeInEditorWorldCommand);

bool FSetRaceGameModeInEditorWorldCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}

	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	
	testWorld->SetGameMode(*FString("/Game/Development/GameModes/BP_Race-GameMode"));
	
	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRaceGameModeSetCommand, FAutomationTestBase*, test);

bool FCheckRaceGameModeSetCommand::Update()
{
	if (GEditor->GetEditorWorldContext().World()->GetMapName() != "VoidWorld")
	{
		return false;
	}
	UWorld* testWorld = GEditor->GetEditorWorldContext().World();
	ARaceGameMode* testGameMode = Cast<ARaceGameMode, AGameModeBase>(UGameplayStatics::GetGameMode(testWorld)));
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

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FSetRaceGameModeInEditorWorldCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRaceGameModeSetCommand(this));

	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS
