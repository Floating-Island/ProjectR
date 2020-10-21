// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackManagerTest.h"


#include "Kismet/GameplayStatics.h"
#include "Track/TrackManager.h"
#include "Mocks/TrackManagerMOCK.h"
#include "Track/TrackGenerator.h"

#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Utilities/PIESessionUtilities.h"


#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.Unit.ClassToTest.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackManagerShouldntBeNullWhenInstantiatedTest, "ProjectR.Unit.TrackManagerTest.ATrackManagerShouldntBeNullWhenInstantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackManagerShouldntBeNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ATrackManager* testManager = NewObject<ATrackManager>();
	{
		TestNotNull(TEXT("The track manager shouldn't be null when instantiated."), testManager);
	}

	return true;
}









DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningATrackManagerAndTrackGeneratorCommand);

bool FSpawningATrackManagerAndTrackGeneratorCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())//if not, everything would be made while the map is loading and the PIE is in progress.
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();


	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	testWorld->SpawnActor<ATrackGenerator>(ATrackGenerator::StaticClass());
	testWorld->SpawnActor<ATrackManagerMOCK>(ATrackManagerMOCK::StaticClass());

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckATrackManagerTrackGeneratorsCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckATrackManagerTrackGeneratorsCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		ATrackManagerMOCK* testManager = Cast<ATrackManagerMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackManagerMOCK::StaticClass()));
		if (testManager)
		{
			bool spawnedTrackGeneratorInTrackManager = testManager->trackGenerators().Contains(Cast<ATrackGenerator, AActor>(UGameplayStatics::GetActorOfClass(testWorld, ATrackGenerator::StaticClass())));

			UE_LOG(LogTemp, Log, TEXT("Track manager %s the track generator listed."), *FString(spawnedTrackGeneratorInTrackManager ? "has" : "doesn't have"));
			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				test->TestTrue(TEXT("The track manager should have track generators already spawned in world."), spawnedTrackGeneratorInTrackManager);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackManagerShouldHaveSpawnedTrackGeneratorsTest, "ProjectR.Unit.TrackManagerTest.ShouldHaveSpawnedTrackGenerators", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackManagerShouldHaveSpawnedTrackGeneratorsTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningATrackManagerAndTrackGeneratorCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckATrackManagerTrackGeneratorsCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}





#endif //WITH_DEV_AUTOMATION_TESTS