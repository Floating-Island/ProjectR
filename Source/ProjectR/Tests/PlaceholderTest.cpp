// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceholderTest.h"


#include "Misc/AutomationTest.h"


#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


//a test
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FOneIsOneTest, "ProjectR.Placeholder Tests.Unit.000: One is one", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


bool FOneIsOneTest::RunTest(const FString& Parameters)
{
	//One should be one.

	TestEqual(TEXT("one is one"), 1, 1);

	return true;
}


//another test
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSTwoIsTwoTest, "ProjectR.Placeholder Tests.Unit.001: Two is two", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


bool FSTwoIsTwoTest::RunTest(const FString& Parameters)
{
	//two should be two.

	TestEqual(TEXT("two is two"), 2, 2);

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS