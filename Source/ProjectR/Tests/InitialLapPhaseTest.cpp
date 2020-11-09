// Fill out your copyright notice in the Description page of Project Settings.


#include "InitialLapPhaseTest.h"

#include "LapPhases/InitialLapPhase.h"
#include "LapPhases/IntermediateLapPhase.h"
#include "Misc/AutomationTest.h"





#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAInitialLapPhaseIsntNullWhenInstantiatedTest, "ProjectR.InitialLapPhase Tests.Unit.000: Isn't null when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAInitialLapPhaseIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AInitialLapPhase* testInitialPhase = NewObject<AInitialLapPhase>();

	TestNotNull(TEXT("The lap shouldn't be null after instantiating it."), testInitialPhase);

	return true;
}






IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAInitialLapPhaseUpdateStateReturnsIntermediateLapPhaseIfItsPassedAsParameterTest, "ProjectR.InitialLapPhase Tests.Unit.001: If a AIntermediateLapPhase instance is passed to updateState, it returns that instance", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAInitialLapPhaseUpdateStateReturnsIntermediateLapPhaseIfItsPassedAsParameterTest::RunTest(const FString& Parameters)
{
	AInitialLapPhase* testInitialPhase = NewObject<AInitialLapPhase>();
	AIntermediateLapPhase* testIntermediateLapPhase = NewObject<AIntermediateLapPhase>();

	TestTrue(TEXT("The initial phase should return the IntermediateLapPhase instance if that is passed as parameter."), testInitialPhase->updatePhase(testIntermediateLapPhase) == testIntermediateLapPhase);

	return true;
}






IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAInitialLapPhaseUpdateStateReturnsItselfIfIntermediateLapPhaseIsntPassedAsParameterTest, "ProjectR.InitialLapPhase Tests.Unit.002: Returns itself if a AIntermediateLapPhase instance isn't passed as parameter in updateState", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAInitialLapPhaseUpdateStateReturnsItselfIfIntermediateLapPhaseIsntPassedAsParameterTest::RunTest(const FString& Parameters)
{
	AInitialLapPhase* testInitialPhase = NewObject<AInitialLapPhase>();

	TestTrue(TEXT("The initial phase should return itself if a IntermediateLapPhase instance isn't passed as parameter of updateState."), testInitialPhase->updatePhase(NewObject<ALapPhase>()) == testInitialPhase);

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS