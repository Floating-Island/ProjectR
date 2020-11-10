// Fill out your copyright notice in the Description page of Project Settings.


#include "LapManagerTest.h"



#include "LapManager/LapManager.h"
#include "Mocks/LapManagerMOCK.h"
#include "LapPhases/InitialLapPhase.h"
#include "LapPhases/IntermediateLapPhase.h"
#include "LapPhases/FinalLapPhase.h"
#include "Jet/Jet.h"

#include "Misc/AutomationTest.h"
#include "Utilities/PIESessionUtilities.h"
#include "Tests/AutomationEditorCommon.h"

#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapManagerIsntNullWhenInstantiatedTest, "ProjectR.LapManager Tests.Unit.000: Isn't null when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapManagerIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ALapManager* testLapManager = NewObject<ALapManager>();

	TestNotNull(TEXT("The lap manager shouldn't be null after instantiating it."), testLapManager);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerAndJetCommand);

bool FSpawningALapManagerAndJetCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	sessionUtilities.spawnInPIEAnInstanceOf<AJet>();
	sessionUtilities.spawnInPIEAnInstanceOf<ALapManager>();

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckALapManagerStoresJetsCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckALapManagerStoresJetsCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		ALapManager* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManager>();
		if (testManager)
		{
			bool hasJetsInWorld = testManager->jetsInPlay().Contains(sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>());

			UE_LOG(LogTemp, Log, TEXT("Lap manager %s the jets listed."), *FString(hasJetsInWorld ? "has" : "doesn't have"));
			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				test->TestTrue(TEXT("The lap manager should have the jets that are already spawned in world."), hasJetsInWorld);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapManagerHasJetsListedWhenSpawnedTest, "ProjectR.LapManager Tests.Integration.001: Has jets listed when spawned", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapManagerHasJetsListedWhenSpawnedTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerAndJetCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckALapManagerStoresJetsCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerAInitialLapPhaseAndJetCommand);

bool FSpawningALapManagerAInitialLapPhaseAndJetCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	sessionUtilities.spawnInPIEAnInstanceOf<AJet>();
	sessionUtilities.spawnInPIEAnInstanceOf<AInitialLapPhase>();
	sessionUtilities.spawnInPIEAnInstanceOf<ALapManagerMOCK>();

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckJetsInitialLapPhaseCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckJetsInitialLapPhaseCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		ALapManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManagerMOCK>();
		if (testManager)
		{
			bool jetsDefaultPhaseIsInitialLapPhase = testManager->defaultLapPhaseIsInitialLapPhase();

			UE_LOG(LogTemp, Log, TEXT("Lap manager jets %s the initial lap phase as default phase."), *FString(jetsDefaultPhaseIsInitialLapPhase ? "have" : "don't have"));

			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				test->TestTrue(TEXT("The lap manager jets should have the initial lap phase as default phase."), jetsDefaultPhaseIsInitialLapPhase);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapManagerJetsHaveInitialLapPhaseAsDefaultPhaseTest, "ProjectR.LapManager Tests.Integration.002: Jets have the initial lap phase as the default phase", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapManagerJetsHaveInitialLapPhaseAsDefaultPhaseTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerAInitialLapPhaseAndJetCommand);
	int tickCount = 0;
	int tickLimit = 1;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetsInitialLapPhaseCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckJetsInitialLapCountCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckJetsInitialLapCountCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		ALapManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManagerMOCK>();
		if (testManager)
		{
			bool jetsInitialLapCountIsOne = testManager->InitialLapCountSetToOne();

			UE_LOG(LogTemp, Log, TEXT("Lap manager jets %s the initial lap count set as one."), *FString(jetsInitialLapCountIsOne ? "have" : "don't have"));

			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				test->TestTrue(TEXT("The lap manager jets should have the initial lap count set to one."), jetsInitialLapCountIsOne);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapManagerJetsHaveInitialLapCountSetToOneTest, "ProjectR.LapManager Tests.Integration.003: Jets have the initial lap count set to one", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapManagerJetsHaveInitialLapCountSetToOneTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerAInitialLapPhaseAndJetCommand);
	int tickCount = 0;
	int tickLimit = 1;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetsInitialLapCountCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerInitalAndIntermediateLapPhasesAndJetCommand);

bool FSpawningALapManagerInitalAndIntermediateLapPhasesAndJetCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	FVector jetLocation = FVector(0, 0, -100);
	sessionUtilities.spawnInPIEAnInstanceOf<AJet>(jetLocation);
	sessionUtilities.spawnInPIEAnInstanceOf<AInitialLapPhase>();
	FVector intermediatePhaseLocation = jetLocation + FVector(0, 0, -20);
	sessionUtilities.spawnInPIEAnInstanceOf<AIntermediateLapPhase>(intermediatePhaseLocation);
	sessionUtilities.spawnInPIEAnInstanceOf<ALapManagerMOCK>();

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckJetChangeFromInitialToIntermediateCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckJetChangeFromInitialToIntermediateCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		ALapManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManagerMOCK>();
		if (testManager)
		{
			bool jetsMovedToIntermediatePhase = testManager->jetsMovedFromInitialToIntermediatePhase();

			UE_LOG(LogTemp, Log, TEXT("Jet location: %s."), *testJet->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jets %s lap phase from initial to intermediate when overlapping intermediate."), *FString(jetsMovedToIntermediatePhase ? "changes" : "doesn't change"));

			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				test->TestTrue(TEXT("The jet should change their lap phase from initial to intermediate when overlapping intermediate."), jetsMovedToIntermediatePhase);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapManagerJetOverlappingIntermediateChangesPhaseToItFromInitialTest, "ProjectR.LapManager Tests.Integration.004: Jet that overlaps with intermediate phase changes to it when coming from initial", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapManagerJetOverlappingIntermediateChangesPhaseToItFromInitialTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerInitalAndIntermediateLapPhasesAndJetCommand);
	int tickCount = 0;
	int tickLimit = 1;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetChangeFromInitialToIntermediateCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerIntermediateAndFinalLapPhasesAndJetCommand);

bool FSpawningALapManagerIntermediateAndFinalLapPhasesAndJetCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	FVector jetLocation = FVector(0, 0, -100);
	sessionUtilities.spawnInPIEAnInstanceOf<AJet>(jetLocation);
	sessionUtilities.spawnInPIEAnInstanceOf<AIntermediateLapPhase>();
	FVector finalPhaseLocation = jetLocation + FVector(0, 0, -20);
	sessionUtilities.spawnInPIEAnInstanceOf<AFinalLapPhase>(finalPhaseLocation);
	ALapManagerMOCK* testManager = sessionUtilities.spawnInPIEAnInstanceOf<ALapManagerMOCK>();
	testManager->makeJetsPhaseIntermediate();

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckJetChangeFromIntermediateToFinalCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckJetChangeFromIntermediateToFinalCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		ALapManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManagerMOCK>();
		if (testManager)
		{
			bool jetsMovedToFinalPhase = testManager->jetsMovedFromIntermediateToFinalPhase();

			UE_LOG(LogTemp, Log, TEXT("Jet location: %s."), *testJet->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jets %s lap phase from intermediate to final when overlapping final."), *FString(jetsMovedToFinalPhase ? "changes" : "doesn't change"));

			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				test->TestTrue(TEXT("The jet should change their lap phase from intermediate to final when overlapping final."), jetsMovedToFinalPhase);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapManagerJetOverlappingFinalChangesPhaseToItFromIntermediateTest, "ProjectR.LapManager Tests.Integration.005: Jet that overlaps with final phase changes to it when coming from intermediate", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapManagerJetOverlappingFinalChangesPhaseToItFromIntermediateTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerIntermediateAndFinalLapPhasesAndJetCommand);
	int tickCount = 0;
	int tickLimit = 1;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetChangeFromIntermediateToFinalCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerInitialAndFinalLapPhasesAndJetCommand);

bool FSpawningALapManagerInitialAndFinalLapPhasesAndJetCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	FVector jetLocation = FVector(0, 0, -100);
	sessionUtilities.spawnInPIEAnInstanceOf<AJet>(jetLocation);
	sessionUtilities.spawnInPIEAnInstanceOf<AFinalLapPhase>();
	FVector initialPhaseLocation = jetLocation + FVector(0, 0, -20);
	sessionUtilities.spawnInPIEAnInstanceOf<AInitialLapPhase>(initialPhaseLocation);
	ALapManagerMOCK* testManager = sessionUtilities.spawnInPIEAnInstanceOf<ALapManagerMOCK>();
	testManager->makeJetsPhaseFinal();

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckJetChangeFromFinalToInitialCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckJetChangeFromFinalToInitialCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		ALapManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ALapManagerMOCK>();
		if (testManager)
		{
			bool jetsMovedToInitialPhase = testManager->jetsMovedFromFinalToInitialPhase();

			UE_LOG(LogTemp, Log, TEXT("Jet location: %s."), *testJet->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jets %s lap phase from final to initial when overlapping initial."), *FString(jetsMovedToInitialPhase ? "changes" : "doesn't change"));

			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				test->TestTrue(TEXT("The jet should change their lap phase from final to initial when overlapping initial."), jetsMovedToInitialPhase);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapManagerJetOverlappingInitialChangesPhaseToItFromFinalTest, "ProjectR.LapManager Tests.Integration.006: Jet that overlaps with initial phase changes to it when coming from final", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapManagerJetOverlappingInitialChangesPhaseToItFromFinalTest::RunTest(const FString& Parameters)
{
	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerInitialAndFinalLapPhasesAndJetCommand);
	int tickCount = 0;
	int tickLimit = 1;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckJetChangeFromFinalToInitialCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS
