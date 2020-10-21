// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackManagerTest.h"

#include "Track/TrackManager.h"

#include "Misc/AutomationTest.h"




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



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackManagerShouldHaveATrackGeneratorTest, "ProjectR.Unit.TrackManagerTest.ATrackManagerShouldHaveATrackGenerator", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FATrackManagerShouldHaveATrackGeneratorTest::RunTest(const FString& Parameters)
{
	ATrackManagerMOCK* testManager = NewObject<ATrackManagerMOCK>();
	{
		TestTrue(TEXT("The track manager shouldn't be null when instantiated."), testManager->hasATrackGenerator());
	}

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS