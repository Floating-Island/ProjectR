// Fill out your copyright notice in the Description page of Project Settings.


#include "IntermediateLapPhaseTest.h"

#include "LapPhases/IntermediateLapPhase.h"
#include "LapPhases/FinalLapPhase.h"
#include "Misc/AutomationTest.h"





#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAIntermediateLapPhaseIsntNullWhenInstantiatedTest, "ProjectR.IntermediateLapPhase Tests.Unit.000: Isn't null when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAIntermediateLapPhaseIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	AIntermediateLapPhase* testIntermediatePhase = NewObject<AIntermediateLapPhase>();

	TestNotNull(TEXT("The intermediate lap phase shouldn't be null after instantiating it."), testIntermediatePhase);

	return true;
}






IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAIntermediateLapPhaseUpdateStateReturnsFinalLapPhaseIfItsPassedAsParameterTest, "ProjectR.IntermediateLapPhase Tests.Unit.001: If a AFinalLapPhase instance is passed to updateState, it returns that instance", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAIntermediateLapPhaseUpdateStateReturnsFinalLapPhaseIfItsPassedAsParameterTest::RunTest(const FString& Parameters)
{
	AIntermediateLapPhase* testIntermediateLapPhase = NewObject<AIntermediateLapPhase>();
	AFinalLapPhase* testFinalLapPhase = NewObject<AFinalLapPhase>();

	TestTrue(TEXT("The intermediate lap phase should return the FinalLapPhase instance if that is passed as parameter of updateState."), testIntermediateLapPhase->updatePhase(testFinalLapPhase) == testFinalLapPhase);

	return true;
}






IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAIntermediateLapPhaseUpdateStateReturnsItselfIfFinalLapPhaseIsntPassedAsParameterTest, "ProjectR.IntermediateLapPhase Tests.Unit.002: Returns itself if a AFinalLapPhase instance isn't passed as parameter in updateState", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAIntermediateLapPhaseUpdateStateReturnsItselfIfFinalLapPhaseIsntPassedAsParameterTest::RunTest(const FString& Parameters)
{
	AIntermediateLapPhase* testIntermediatePhase = NewObject<AIntermediateLapPhase>();

	TestTrue(TEXT("The intermediate phase should return itself if a FinalLapPhase instance isn't passed as parameter of updateState."), testIntermediatePhase->updatePhase(NewObject<ALapPhase>()) == testIntermediatePhase);

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS