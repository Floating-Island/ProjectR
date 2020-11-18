// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceGameModeTest.h"




#include "GameMode/RaceGameMode.h"
#include "Mocks/RaceGameModeMOCK.h"
#include "Jet/Jet.h"
#include "Track/TrackGenerator.h"
#include "LapPhases/InitialLapPhase.h"
#include "LapManager/LapManager.h"
#include "GameMode/RaceStages/RacePreparationStage.h"
#include "GameMode/RaceStages/RaceBeginningStage.h"
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
	UWorld* testWorld = sessionUtilities.currentPIEWorld();
	ARaceGameMode* testGameMode = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameMode>();
	if (testGameMode)
	{
		test->TestNotNull(TEXT("Race game mode was succesfully set as game mode in the world."), testGameMode);
		testWorld->bDebugFrameStepExecution = true;
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

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckRaceGameModeCreatesAllJetsCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckRaceGameModeCreatesAllJetsCommand::Update()
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
		int expectedNumberOfJets = testGameMode->jetsToSpawn();
		TArray<AJet*> worldJets = sessionUtilities.retrieveFromPIEAllInstancesOf<AJet>();
		bool sameNumberOfJetsInGameMode = gameModeJets.Num() == worldJets.Num() && expectedNumberOfJets == worldJets.Num();

		UE_LOG(LogTemp, Log, TEXT("Expected number of jets: %d."), expectedNumberOfJets);
		UE_LOG(LogTemp, Log, TEXT("Number of race game mode jets: %d."), gameModeJets.Num());
		UE_LOG(LogTemp, Log, TEXT("Number of world jets: %d."), worldJets.Num());
		UE_LOG(LogTemp, Log, TEXT("The race game mode %s the jets in the world."), *FString(sameNumberOfJetsInGameMode ? "has" : "doesn't have"));

		if (sameNumberOfJetsInGameMode)
		{
			test->TestTrue(TEXT("Race game mode should have the same number of jets than the world."), sameNumberOfJetsInGameMode);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}

		++aTickCount;
		if (aTickCount > aTickLimit)
		{
			test->TestTrue(TEXT("Tick limit reached. Race game mode should have the same number of jets than the world."), sameNumberOfJetsInGameMode);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceGameModeCreatesExpectedNumberOfJetsTest, "ProjectR.RaceGameMode Tests.Integration.002: Creates the same amount of jets as specified in class settings", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FARaceGameModeCreatesExpectedNumberOfJetsTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameMode");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	int tickCount = 0;
	int tickLimit = 2;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckRaceGameModeCreatesAllJetsCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckRaceGameModeJetsPositioningCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckRaceGameModeJetsPositioningCommand::Update()
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
		int expectedNumberOfJets = testGameMode->jetsToSpawn();
		bool sameNumberOfJetsInGameMode = gameModeJets.Num() == expectedNumberOfJets;
		ATrackGenerator* testTrack = sessionUtilities.retrieveFromPIEAnInstanceOf<ATrackGenerator>();
		AInitialLapPhase* initialPhase = testGameMode->initialLapPhase();
		float distanceBetweenPhaseAndTrack = testTrack->distanceAlongSplineOf(initialPhase);
		if (FMath::IsNearlyZero(distanceBetweenPhaseAndTrack))
		{
			UE_LOG(LogTemp, Log, TEXT("Distance between initial lap phase and track: %f."), distanceBetweenPhaseAndTrack);
			distanceBetweenPhaseAndTrack = testTrack->length();
			UE_LOG(LogTemp, Log, TEXT("Distance between initial lap phase and track: %f. If there's difference, the initial phase is at origin."), distanceBetweenPhaseAndTrack);
		}

		bool jetsAreBehindInitialPhase = true;
		for (const auto& jet : gameModeJets)
		{
			float distanceBetweenJetAndTrack = testTrack->distanceAlongSplineOf(jet);
			UE_LOG(LogTemp, Log, TEXT("Distance between jet and track: %f."), distanceBetweenJetAndTrack);
			if (distanceBetweenJetAndTrack > distanceBetweenPhaseAndTrack)
			{
				jetsAreBehindInitialPhase = false;
				break;
			}
		}

		UE_LOG(LogTemp, Log, TEXT("Expected number of jets: %d."), expectedNumberOfJets);
		UE_LOG(LogTemp, Log, TEXT("Number of race game mode jets: %d."), gameModeJets.Num());


		if (sameNumberOfJetsInGameMode && jetsAreBehindInitialPhase)
		{
			test->TestTrue(TEXT("Race game mode should position the jets behind the initial lap phase."), sameNumberOfJetsInGameMode && jetsAreBehindInitialPhase);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}

		++aTickCount;
		if (aTickCount > aTickLimit)
		{
			test->TestTrue(TEXT("Tick limit reached. Race game mode should position the jets behind the initial lap phase."), sameNumberOfJetsInGameMode && jetsAreBehindInitialPhase);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceGameModePositionsJetsBehindTheInitialLapPhaseTest, "ProjectR.RaceGameMode Tests.Integration.003: Positions jets behind the initial lap phase", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FARaceGameModePositionsJetsBehindTheInitialLapPhaseTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameMode");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	int tickCount = 0;
	int tickLimit = 2;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckRaceGameModeJetsPositioningCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRaceGameModeUpdateStageCommand, FAutomationTestBase*, test);

bool FCheckRaceGameModeUpdateStageCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.currentPIEWorld();
	ARaceGameModeMOCK* testGameMode = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameModeMOCK>();

	ARacePreparationStage* testPreparation = sessionUtilities.spawnInPIEAnInstanceOf<ARacePreparationStage>();
	testGameMode->changeStageTo(testPreparation);

	testGameMode->updateStage(testPreparation);

	bool changedStage = ARaceBeginningStage::StaticClass() == testGameMode->currentStage()->GetClass();

	test->TestTrue(TEXT("Race game mode changes the stage to the next when calling updateStage."), changedStage);
	testWorld->bDebugFrameStepExecution = true;
	return true;

}


//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceGameModeUpdateStageBringsNextStageTest, "ProjectR.RaceGameMode Tests.Unit.004: updateStage changes the stage to the next stage", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FARaceGameModeUpdateStageBringsNextStageTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FCheckRaceGameModeUpdateStageCommand(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FSpawnAJetBehindAnotherCommand, FAutomationTestBase*, test);

bool FSpawnAJetBehindAnotherCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	UWorld* testWorld = sessionUtilities.currentPIEWorld();
	ARaceGameModeMOCK* testGameMode = sessionUtilities.retrieveFromPIEAnInstanceOf<ARaceGameModeMOCK>();

	ATrackGenerator* testTrack = sessionUtilities.retrieveFromPIEAnInstanceOf<ATrackGenerator>();

	float behindDistance = 300;
	int height = 200;
	FVector behind = testTrack->locationAt(behindDistance) + testTrack->upVectorAt(behindDistance) * height;
	float aheadDistance = 1200;
	FVector ahead = testTrack->locationAt(aheadDistance) + testTrack->upVectorAt(aheadDistance) * height;;

	AJet* jetBehind = sessionUtilities.spawnInPIEAnInstanceOf<AJet>(behind);
	AJet* jetAhead = sessionUtilities.spawnInPIEAnInstanceOf<AJet>(ahead);

	testGameMode->createLapManager();
	
	testGameMode->addToRunningJets(jetBehind);
	testGameMode->addToRunningJets(jetAhead);

	TMap<AJet*, int8> positions = testGameMode->jetPositions();

	bool correctPositions = *positions.Find(jetAhead) < *positions.Find(jetBehind);

	test->TestTrue(TEXT("A jet ahead of another should have its position number lower than the one behind."), correctPositions);
	testWorld->bDebugFrameStepExecution = true;
	return true;

}


//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceGameModePositionNumberLowerThanTheOneBehindTest, "ProjectR.RaceGameMode Tests.Integration.005: The position number of a jet is lower than the jet behind", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FARaceGameModePositionNumberLowerThanTheOneBehindTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld-RaceGameModeMOCK");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawnAJetBehindAnotherCommand(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS
