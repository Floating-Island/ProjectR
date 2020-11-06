// Fill out your copyright notice in the Description page of Project Settings.


#include "LapTest.h"

#include "LapPhases/Lap.h"
#include "LapPhases/Phase1.h"
#include "Misc/AutomationTest.h"





#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapIsntNullWhenInstantiatedTest, "ProjectR.Lap Tests.Unit.000: Isn't null when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ALap* testLap = NewObject<ALap>();

	TestNotNull(TEXT("The lap shouldn't be null after instantiating it."), testLap);

	return true;
}






IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapUpdateStateReturnsPhase1IfItsPassedAsParameterTest, "ProjectR.Lap Tests.Unit.001: If a Phase1 instance is passed to updateState, it returns the Phase1 instance", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapUpdateStateReturnsPhase1IfItsPassedAsParameterTest::RunTest(const FString& Parameters)
{
	ALap* testLap = NewObject<ALap>();
	APhase1* testPhase1 = NewObject<APhase1>();

	TestTrue(TEXT("The lap should return the Phase1 instance if that is passed as parameter."), testLap->updateState(testPhase1) == testPhase1);

	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS