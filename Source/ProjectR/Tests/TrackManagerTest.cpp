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

	sessionUtilities.spawnTrackManagerInPie();

	FRotator arbitraryRotator = FRotator(0, 0, 135);
	testGenerator->SetActorRotation(arbitraryRotator);
	
	FVector generatorDirection = testGenerator->GetActorUpVector();
	float magnetBoxDistanceToFloor = 400;
	FVector jetLoctation = generatorDirection * magnetBoxDistanceToFloor;

	sessionUtilities.spawnJetInPIE(jetLoctation);

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckATrackManagerAttractsJetsCommand, int, aTickCount, int, aTickLimit, float, aPreviousDistance, FAutomationTestBase*, test);

bool FCheckATrackManagerAttractsJetsCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		ATrackGenerator* testGenerator = sessionUtilities.retrieveTrackGeneratorFromPIE();
		AJet* testJet = sessionUtilities.retrieveJetFromPIE();
		if (testGenerator && testJet)
		{
			float currentDistance = (testJet->GetActorLocation() - testGenerator->GetActorLocation()).Size();
			bool isPulling = currentDistance < aPreviousDistance;
			bool isVelocityFullyAlongNormal = FMath::IsNearlyEqual(testJet->GetVelocity().ProjectOnTo(testGenerator->GetActorUpVector()).Size(), testJet->GetVelocity().Size(), 0.1f);
			bool velocityNearZero = FMath::IsNearlyZero(testJet->GetVelocity().Size(), 0.1f);

			UE_LOG(LogTemp, Log, TEXT("previous distance between track generator and jet: %f"), aPreviousDistance);
			UE_LOG(LogTemp, Log, TEXT("current distance between track generator and jet: %f"), currentDistance);
			UE_LOG(LogTemp, Log, TEXT("Jet location: %s"), *testJet->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Track generator location: %s"), *testGenerator->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet velocity: %s"), *testJet->GetVelocity().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet velocity projection on normal vector: %s"), *testJet->GetVelocity().ProjectOnTo(testGenerator->GetActorUpVector()).ToString());
			UE_LOG(LogTemp, Log, TEXT("Track generator normal vector: %s"), *testGenerator->GetActorUpVector().ToString());
			UE_LOG(LogTemp, Log, TEXT("is pulling: %s"), *FString(isPulling? "true" : "false"));
			UE_LOG(LogTemp, Log, TEXT("is velocity fully along normal: %s"), *FString(isVelocityFullyAlongNormal? "true" : "false"));
			UE_LOG(LogTemp, Log, TEXT("is velocity near zero: %s"), *FString(velocityNearZero? "true" : "false"));
			
			if (!velocityNearZero && isVelocityFullyAlongNormal && isPulling)
			{
				test->TestTrue(TEXT("The track generator should attract a Jet along the track normal vector when a track manager is present."), !velocityNearZero && isVelocityFullyAlongNormal && isPulling);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			
			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				test->TestFalse(TEXT("Tick limit reached for this test. The track generator didn't attract the jet along the track normal vector when a track manager was present."), aTickCount > aTickLimit);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			aPreviousDistance = currentDistance;
		}
	}
	return false;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackManagerShouldAttractJetsTowardsTrackGeneratorsTest, "ProjectR.Unit.TrackManagerTest.ShouldAttractJetsTowardsTrackGenerators", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackManagerShouldAttractJetsTowardsTrackGeneratorsTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningATrackManagerARotatedTrackGeneratorAndJetCloseToItCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckATrackManagerAttractsJetsCommand(tickCount, tickLimit, std::numeric_limits<float>::min(), this));

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