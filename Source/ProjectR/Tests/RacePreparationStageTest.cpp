// Fill out your copyright notice in the Description page of Project Settings.


#include "RacePreparationStageTest.h"

#include "GameMode/RaceStages/RacePreparationStage.h"

#include "Misc/AutomationTest.h"


#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARacePreparationStageIsntNullWhenInstantiatedTest, "ProjectR.RacePreparationStage Tests.Unit.000: Isn't null when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FARacePreparationStageIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ARacePreparationStage* testRacePreparationStage = NewObject<ARacePreparationStage>();

	TestNotNull(TEXT("The race preparation stage shouldn't be null after instantiating it."), testRacePreparationStage);

	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS

