// Fill out your copyright notice in the Description page of Project Settings.


#include "JetTest.h"

#include "Jet.h"

#include "Misc/AutomationTest.h"


#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.Unit.ClassToTest.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldntBeNullWhenInstantiatedTest, "ProjectR.Unit.JetTests.ShouldntBeNullWhenInstantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldntBeNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	{
		AJet* testJet = NewObject<AJet>();
		
		TestNotNull(TEXT("The Jet shouldn't be null after instantiating it."), testJet);
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpeedIsZeroWhenInstantiatedTest, "ProjectR.Unit.JetTests.SpeedIsZeroWhenInstantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetSpeedIsZeroWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	{
		AJet* testJet = NewObject<AJet>();
		
		TestTrue(TEXT("Jet speed should be zero when instantiated."), testJet->currentSpeed() == 0);
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpeedIncreasesWhenAcceleratesTest, "ProjectR.Unit.JetTests.SpeedIncreasesWhenAccelerates", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetSpeedIncreasesWhenAcceleratesTest::RunTest(const FString& Parameters)
{
	{
		AJet* testJet = NewObject<AJet>();

		float currentSpeed = testJet->currentSpeed();

		testJet->accelerate();

		float acceleratedSpeed = testJet->currentSpeed();
		
		TestTrue(TEXT("Speed increases when accelerates."), acceleratedSpeed > currentSpeed);
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetBrakeMakesItGoReverseWhenSpeedIsZeroTest, "ProjectR.Unit.JetTests.BrakeMakesItGoReverseWhenSpeedIsZero", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetBrakeMakesItGoReverseWhenSpeedIsZeroTest::RunTest(const FString& Parameters)
{
	{
		AJet* testJet = NewObject<AJet>();

		//another test checks that the current speed is zero when instantiated

		testJet->brake();
		
		TestTrue(TEXT("Brake becomes Reverse when speed is zero or negative"), testJet->currentSpeed() < 0 );
	}

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS