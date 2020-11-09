// Fill out your copyright notice in the Description page of Project Settings.


#include "LapManagerTest.h"

#include "LapManager/LapManager.h"
#include "Mocks/LapManagerMOCK.h"
#include "LapPhases/InitialLapPhase.h"
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



#endif //WITH_DEV_AUTOMATION_TESTS
