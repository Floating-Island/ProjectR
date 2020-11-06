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


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapIsntNullWhenInstantiatedTest, "ProjectR.InitialLapPhase Tests.Unit.000: Isn't null when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AInitialLapPhase* testInitialPhase = NewObject<AInitialLapPhase>();

	TestNotNull(TEXT("The lap shouldn't be null after instantiating it."), testLap);

	return true;
}






IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapUpdateStateReturnsIntermediateLapPhaseIfItsPassedAsParameterTest, "ProjectR.InitialLapPhase Tests.Unit.001: If a AIntermediateLapPhase instance is passed to updateState, it returns that instance", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapUpdateStateReturnsIntermediateLapPhaseIfItsPassedAsParameterTest::RunTest(const FString& Parameters)
{
	AInitialLapPhase* testInitialPhase = NewObject<AInitialLapPhase>();
	AIntermediateLapPhase* testIntermediateLapPhase = NewObject<AIntermediateLapPhase>();

	TestTrue(TEXT("The initial phase should return the IntermediateLapPhase instance if that is passed as parameter."), testInitialPhase->updatePhase(testIntermediateLapPhase) == testIntermediateLapPhase);

	return true;
}






IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapUpdateStateReturnsItselfIfIntermediateLapPhaseIsntPassedAsParameterTest, "ProjectR.InitialLapPhase Tests.Unit.002: Returns itself if a AIntermediateLapPhase instance as parameter in updateState", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapUpdateStateReturnsItselfIfIntermediateLapPhaseIsntPassedAsParameterTest::RunTest(const FString& Parameters)
{
	AInitialLapPhase* testInitialPhase = NewObject<AInitialLapPhase>();
	AIntermediateLapPhase* testIntermediateLapPhase = NewObject<AIntermediateLapPhase>();

	TestTrue(TEXT("The initial phase should return itself if a IntermediateLapPhase instance ins't passed as parameter of updateState."), testInitialPhase->updatePhase(NewObject<ALapPhase>()) == testIntermediateLapPhase);

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS