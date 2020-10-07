// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackTest.h"

#include "Track.h"
#include "Mocks/TrackMOCK.h"
#include "Mocks/JetMOCK.h"

#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Utilities/PIESessionUtilities.h"


#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.Unit.ClassToTest.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackShouldntBeNullWhenInstantiatedTest, "ProjectR.Unit.TrackTest.ATrackShouldntBeNullWhenInstantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


bool FATrackShouldntBeNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ATrack* testTrack = NewObject<ATrack>();
	{
		TestNotNull(TEXT("The track shouldn't be null when instantiated"), testTrack);
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackShouldHaveAFloorTest, "ProjectR.Unit.TrackTest.ATrackShouldHaveAFloor", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackShouldHaveAFloorTest::RunTest(const FString& Parameters)
{
	ATrackMOCK* testTrack = NewObject<ATrackMOCK>();
	{
		TestTrue(TEXT("The track should have a floor so jets can step in."), testTrack->hasAFloor());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackFloorShouldHaveAStaticMeshTest, "ProjectR.Unit.TrackTest.ATrackFloorShouldHaveAStaticMesh", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackFloorShouldHaveAStaticMeshTest::RunTest(const FString& Parameters)
{
	ATrackMOCK* testTrack = NewObject<ATrackMOCK>();
	{
		TestTrue(TEXT("The track floor should have a static mesh attached."), testTrack->floorHasStaticMesh());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackShouldHaveAMagnetBoxTest, "ProjectR.Unit.TrackTest.ATrackShouldHaveAMagnetBox", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackShouldHaveAMagnetBoxTest::RunTest(const FString& Parameters)
{
	ATrackMOCK* testTrack = NewObject<ATrackMOCK>();
	{
		TestTrue(TEXT("The track should have a magnet box so it catches jets when the track rotates."), testTrack->hasAMagnetBox());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackMagnetBoxShouldBeAttachedToRootTest, "ProjectR.Unit.TrackTest.ATrackMagnetBoxShouldBeAttachedToRoot", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackMagnetBoxShouldBeAttachedToRootTest::RunTest(const FString& Parameters)
{
	ATrackMOCK* testTrack = NewObject<ATrackMOCK>();
	{
		TestTrue(TEXT("The track magnet box should be attached to the root component."), testTrack->magnetBoxAttachedToRoot());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackMagnetBoxShouldHaveCollisionsEnabledToQueryOnlyTest, "ProjectR.Unit.TrackTest.ATrackMagnetBoxShouldHaveCollisionsEnabledToQueryOnly", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackMagnetBoxShouldHaveCollisionsEnabledToQueryOnlyTest::RunTest(const FString& Parameters)
{
	ATrackMOCK* testTrack = NewObject<ATrackMOCK>();
	{
		TestTrue(TEXT("The track magnet box should have collisions enabled to query only."), testTrack->magnetBoxHasCollisionsEnabledToQueryOnly());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackMagnetBoxShouldOverlapWithPawnChannelTest, "ProjectR.Unit.TrackTest.ATrackMagnetBoxShouldOverlapWithPawnChannel", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackMagnetBoxShouldOverlapWithPawnChannelTest::RunTest(const FString& Parameters)
{
	ATrackMOCK* testTrack = NewObject<ATrackMOCK>();
	{
		TestTrue(TEXT("The track magnet box should overlap with the pawn channel."), testTrack->magnetBoxOverlapsPawnChannel());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackMagnetBoxGeneratesOverlapEventsTest, "ProjectR.Unit.TrackTest.ATrackMagnetBoxGeneratesOverlapEvents", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackMagnetBoxGeneratesOverlapEventsTest::RunTest(const FString& Parameters)
{
	ATrackMOCK* testTrack = NewObject<ATrackMOCK>();
	{
		TestTrue(TEXT("The track magnet box should generate overlap events."), testTrack->magnetBoxGeneratesOverlapEvents());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMeshCollisionTypeShouldBePawnTest, "ProjectR.Unit.TrackTest.AJetMeshCollisionTypeShouldBePawn", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetMeshCollisionTypeShouldBePawnTest::RunTest(const FString& Parameters)
{
	AJetMOCK* testJet = NewObject<AJetMOCK>();
	{
		TestTrue(TEXT("The jet collision object type should be pawn."), testJet->meshCollisionIsPawn());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMeshComponentShouldGenerateOverlapEventsTest, "ProjectR.Unit.TrackTest.AJetMeshComponentShouldGenerateOverlapEvents", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetMeshComponentShouldGenerateOverlapEventsTest::RunTest(const FString& Parameters)
{
	AJetMOCK* testJet = NewObject<AJetMOCK>();
	{
		TestTrue(TEXT("The Jet meshComponent should generate overlap events so the Track gets notified."), testJet->generatesOverlapEvents());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackMagnetBoxShouldHaveVolumeTest, "ProjectR.Unit.TrackTest.ATrackMagnetBoxShouldHaveVolume", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackMagnetBoxShouldHaveVolumeTest::RunTest(const FString& Parameters)
{
	ATrackMOCK* testTrack = NewObject<ATrackMOCK>();
	{
		TestTrue(TEXT("The magnet box should have a box volume."), testTrack->magnetBoxHasVolume());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackMagnetBoxShouldBeHiddenTest, "ProjectR.Unit.TrackTest.ATrackMagnetBoxShouldBeHidden", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackMagnetBoxShouldBeHiddenTest::RunTest(const FString& Parameters)
{
	ATrackMOCK* testTrack = NewObject<ATrackMOCK>();
	{
		TestTrue(TEXT("The magnet box should be hidden."), testTrack->magnetBoxIsHidden());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackMagnetBoxShouldBeOnTopOfFloorTest, "ProjectR.Unit.TrackTest.ATrackMagnetBoxShouldBeOnTopOfFloor", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackMagnetBoxShouldBeOnTopOfFloorTest::RunTest(const FString& Parameters)
{
	ATrackMOCK* testTrack = NewObject<ATrackMOCK>();
	{
		TestTrue(TEXT("The magnet box should be on top of the floor."), testTrack->magnetBoxOnTopOfFloor());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackMagnetBoxShouldMatchFloorXYExtensionTest, "ProjectR.Unit.TrackTest.ATrackMagnetBoxShouldMatchFloorXYExtension", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackMagnetBoxShouldMatchFloorXYExtensionTest::RunTest(const FString& Parameters)
{
	ATrackMOCK* testTrack = NewObject<ATrackMOCK>();
	{
		TestTrue(TEXT("The magnet box should have the floor XY extension."), testTrack->magnetBoxHasXYFloorExtension());
	}

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndTrackUpsideDownCommand);

bool FSpawningAJetAndTrackUpsideDownCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	ATrackMOCK* testTrack = sessionUtilities.spawnTrackMOCKInPie();
	FRotator upsideDown = FRotator(180, 0, 0);
	testTrack->SetActorRotation(upsideDown);

	FVector distanceFromTrack = FVector(0, 0, 400);
	FVector beneathTheTrack = testTrack->GetActorLocation() - distanceFromTrack;

	AJet* testJet = sessionUtilities.spawnJetInPIE(beneathTheTrack);
	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckATrackAttractsAJetCommand, int, aTickCount, int, aTickLimit, float, aPreviousDistance, FAutomationTestBase*, test);

bool FCheckATrackAttractsAJetCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJet* testJet = sessionUtilities.retrieveJetFromPIE();
		ATrackMOCK* testTrack = sessionUtilities.retrieveTrackMOCKFromPIE();

		if (testJet && testTrack)
		{
			++aTickCount;
			float currentDistance = (testJet->GetActorLocation() - testTrack->GetActorLocation()).Size();
			bool isPulling = currentDistance < aPreviousDistance;
			bool isVelocityFullyAlongNormal = FMath::IsNearlyEqual(testJet->GetVelocity().ProjectOnTo(testTrack->normalVector()).Size(), testJet->GetVelocity().Size());
			bool velocityNearZero = FMath::IsNearlyZero(testJet->GetVelocity().Size(), 0.1f);

			GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("Jet location: %s"), *testJet->GetActorLocation().ToString()));
			GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("Track location: %s"), *testTrack->GetActorLocation().ToString()));
			GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("Jet velocity: %s"), *testJet->GetVelocity().ToString()));
			GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("Jet velocity projection on normal vector: %s"), *testJet->GetVelocity().ProjectOnTo(testTrack->normalVector()).ToString()));
			GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("Track normal vector: %s"), *testTrack->normalVector().ToString()));
			UE_LOG(LogTemp, Log, TEXT("previous distance between track and jet: %f"), aPreviousDistance);
			UE_LOG(LogTemp, Log, TEXT("current distance between track and jet: %f"), currentDistance);
			UE_LOG(LogTemp, Log, TEXT("Jet location: %s"), *testJet->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Track location: %s"), *testTrack->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet velocity: %s"), *testJet->GetVelocity().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet velocity projection on normal vector: %s"), *testJet->GetVelocity().ProjectOnTo(testTrack->normalVector()).ToString());
			UE_LOG(LogTemp, Log, TEXT("Track normal vector: %s"), *testTrack->normalVector().ToString());
			UE_LOG(LogTemp, Log, TEXT("is pulling: %s"), isPulling? "true" : "false");
			UE_LOG(LogTemp, Log, TEXT("is velocity fully along normal: %s"), isVelocityFullyAlongNormal? "true" : "false");
			UE_LOG(LogTemp, Log, TEXT("is velocity near zero: %s"), velocityNearZero? "true" : "false");
			
			if (!velocityNearZero && isVelocityFullyAlongNormal && isPulling)
			{
				test->TestTrue(TEXT("The Track should attract a Jet along the track normal vector."), !velocityNearZero && isVelocityFullyAlongNormal && isPulling);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			++aTickCount;

			if (aTickCount > aTickLimit)
			{
				test->TestFalse(TEXT("Tick limit reached for this test. The Track didn't attract the jet along the track normal vector."), aTickCount > aTickLimit);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			aPreviousDistance = currentDistance;
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackUpsideDownShouldAttractAJetAlongItsNormalVectorTest, "ProjectR.Unit.TrackTest.UpsideDownShouldAttractAJetAlongItsNormalVector", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackUpsideDownShouldAttractAJetAlongItsNormalVectorTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndTrackUpsideDownCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckATrackAttractsAJetCommand(tickCount, tickLimit, std::numeric_limits<float>::min(), this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndTrackSideWaysCommand);

bool FSpawningAJetAndTrackSideWaysCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	ATrackMOCK* testTrack = sessionUtilities.spawnTrackMOCKInPie();
	FRotator sideways = FRotator(0, 0, 90);
	testTrack->SetActorRotation(sideways);

	FVector distanceFromTrack = FVector(0, 900, 0); 
	FVector nearTheTrack = testTrack->GetActorLocation() + distanceFromTrack;

	AJet* testJet = sessionUtilities.spawnJetInPIE(nearTheTrack);
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackSideWaysShouldAttractAJetAlongItsNormalVectorTest, "ProjectR.Unit.TrackTest.SideWaysShouldAttractAJetAlongItsNormalVector", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackSideWaysShouldAttractAJetAlongItsNormalVectorTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndTrackSideWaysCommand);
	int tickCount = 0;
	int tickLimit = 4;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckATrackAttractsAJetCommand(tickCount, tickLimit, std::numeric_limits<float>::min(), this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}



//we need another test to check that we cancel gravity... We do, but it's not on the tests...






#endif //WITH_DEV_AUTOMATION_TESTS