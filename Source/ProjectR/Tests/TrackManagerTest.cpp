// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackManagerTest.h"


#include "Kismet/GameplayStatics.h"
#include "Track/TrackManager.h"
#include "Mocks/TrackManagerMOCK.h"
#include "Track/TrackGenerator.h"
#include "Jet/Jet.h"

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
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();


	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	sessionUtilities.spawnTrackGeneratorInPie();
	sessionUtilities.spawnTrackManagerMOCKInPie();

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckATrackManagerTrackGeneratorsCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckATrackManagerTrackGeneratorsCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		ATrackManagerMOCK* testManager = sessionUtilities.retrieveTrackManagerMOCKFromPIE();
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









DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningATrackManagerARotatedTrackGeneratorAndJetCloseToItCommand);

bool FSpawningATrackManagerARotatedTrackGeneratorAndJetCloseToItCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();


	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	ATrackGenerator* testGenerator = sessionUtilities.spawnTrackGeneratorInPie();

	sessionUtilities.spawnTrackManagerMOCKInPie();

	FRotator arbitraryRotator = FRotator(0, 0, 135);
	testGenerator->SetActorRotation(arbitraryRotator);
	
	FVector generatorDirection = testGenerator->GetActorUpVector();
	float magnetBoxDistanceToFloor = 400;
	FVector jetLoctation = generatorDirection * magnetBoxDistanceToFloor;

	sessionUtilities.spawnJetInPIE(jetLoctation);

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckATrackManagerStoresJetsWhenOverlapCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckATrackManagerStoresJetsWhenOverlapCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		ATrackManagerMOCK* testManager = sessionUtilities.retrieveTrackManagerMOCKFromPIE();
		if (testManager)
		{
			bool hasJetsStored = testManager->hasJetsStored();
			UE_LOG(LogTemp, Log, TEXT("track manager has jets stored: %s"), *FString(hasJetsStored? "true" : "false"));
			
			if (hasJetsStored)
			{
				test->TestTrue(TEXT("The track manager should store the jets that overlap with a track generator's magnet box."), hasJetsStored);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			
			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				test->TestFalse(TEXT("Tick limit reached for this test. The track manager didn't store the jets that overlapped with a track generator's magnet box."), aTickCount > aTickLimit);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackManagerShouldStoreJetsOverlappingWithTrackGeneratorsTest, "ProjectR.Unit.TrackManagerTest.ShouldStoreJetsOverlappingWithTrackGenerators", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackManagerShouldStoreJetsOverlappingWithTrackGeneratorsTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningATrackManagerARotatedTrackGeneratorAndJetCloseToItCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckATrackManagerStoresJetsWhenOverlapCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}




//make the magnet box broadcast on begin overlap and on end overlap events (it's automatic once we generate overlap events).
//make a track manager to catch those events, add the overlapped pawns to a owning set and every frame travel the set and magnetize pawns this way:
//1) get the jet location.
//2) search along the spline the nearest point to the jet location.
//3) trace a line from the jet towards the nearest spline location (it will hit the spline mesh surface).
//4) get the normal of that surface (from the hit result).
//5) cancel gravity.
//6) apply gravity contrary to the surface normal (it needs to pull), like how it's done in the track.





#endif //WITH_DEV_AUTOMATION_TESTS