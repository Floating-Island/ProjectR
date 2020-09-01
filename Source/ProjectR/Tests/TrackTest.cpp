// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackTest.h"

#include "Track.h"

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

#endif //WITH_DEV_AUTOMATION_TESTS