// Fill out your copyright notice in the Description page of Project Settings.


#include "JetMOCKTest.h"

#include "Mocks/JetMOCK.h"

#include "Misc/AutomationTest.h"


#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.Unit.ClassToTest.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJetMockShouldntBeNullWhenInstantiatedTest, "ProjectR.Unit.JetMockTests.JetMockShouldntBeNullWhenInstantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


bool FJetMockShouldntBeNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	
	{
		AJetMOCK* testMockJet = NewObject<AJetMOCK>();
		
		TestNotNull(TEXT("The Jet shouldn't be null after instantiating it."), testMockJet);
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJetMockSettingSpeedChangesSpeedToDesiredTest, "ProjectR.Unit.JetMockTests.JetMockSettingSpeedChangesSpeedToDesired", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


bool FJetMockSettingSpeedChangesSpeedToDesiredTest::RunTest(const FString& Parameters)
{
	
	{
		AJetMOCK* testMockJet = NewObject<AJetMOCK>();

		float aDesiredSpeed = 30.0f;
		
		testMockJet->setCurrentSpeedTo(aDesiredSpeed);
		
		TestTrue(TEXT("Setting speed should change the speed to a desired one."), testMockJet->currentSpeed() == aDesiredSpeed );
	}

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS