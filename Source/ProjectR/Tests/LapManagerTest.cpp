// Fill out your copyright notice in the Description page of Project Settings.


#include "LapManagerTest.h"

#include "LapManager/LapManager.h"
#include "Misc/AutomationTest.h"





#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapManagerIsntNullWhenInstantiatedTest, "ProjectR.LapManager Tests.Unit.000: Isn't null when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapManagerIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ALapManager* testLapManager = NewObject<ALapManager>();

	TestNotNull(TEXT("The lap manager shouldn't be null after instantiating it."), testLapManager);

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS
