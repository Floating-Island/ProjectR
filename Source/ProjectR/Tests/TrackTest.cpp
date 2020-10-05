// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackTest.h"

#include "Track.h"
#include "Mocks/TrackMOCK.h"

#include "Misc/AutomationTest.h"


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



#endif //WITH_DEV_AUTOMATION_TESTS