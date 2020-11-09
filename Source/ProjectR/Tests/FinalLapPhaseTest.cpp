// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalLapPhaseTest.h"

#include "LapPhases/FinalLapPhase.h"
#include "LapPhases/InitialLapPhase.h"
#include "Misc/AutomationTest.h"





#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAFinalLapPhaseIsntNullWhenInstantiatedTest, "ProjectR.FinalLapPhase Tests.Unit.000: Isn't null when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAFinalLapPhaseIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AFinalLapPhase* testFinalPhase = NewObject<AFinalLapPhase>();

	TestNotNull(TEXT("The final lap phase shouldn't be null after instantiating it."), testFinalPhase);

	return true;
}






IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAFinalLapPhaseUpdateStateReturnsInitialLapPhaseIfItsPassedAsParameterTest, "ProjectR.FinalLapPhase Tests.Unit.001: If a AInitialLapPhase instance is passed to updateState, it returns that instance", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAFinalLapPhaseUpdateStateReturnsInitialLapPhaseIfItsPassedAsParameterTest::RunTest(const FString& Parameters)
{
	AFinalLapPhase* testFinalLapPhase = NewObject<AFinalLapPhase>();
	AInitialLapPhase* testInitialLapPhase = NewObject<AInitialLapPhase>();

	TestTrue(TEXT("The final lap phase should return the InitialLapPhase instance if that is passed as parameter."), testFinalLapPhase->updatePhase(testInitialLapPhase) == testInitialLapPhase);

	return true;
}


#endif //WITH_DEV_AUTOMATION_TESTS