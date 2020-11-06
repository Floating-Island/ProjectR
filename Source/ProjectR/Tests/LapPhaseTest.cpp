// Fill out your copyright notice in the Description page of Project Settings.


#include "LapPhaseTest.h"

#include "LapPhases/LapPhase.h"
#include "Mocks/LapPhaseMOCK.h"

#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Editor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"




#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseIsntNullWhenInstantiatedTest, "ProjectR.LapPhases Tests.Unit.000: Isn't null when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapPhaseIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	ALapPhase* testLapPhase = NewObject<ALapPhase>();

	TestNotNull(TEXT("The LapPhase shouldn't be null after instantiating it."), testLapPhase);

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseHasAStaticMeshComponentTest, "ProjectR.LapPhases Tests.Unit.001: Has a static mesh component", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapPhaseHasAStaticMeshComponentTest::RunTest(const FString& Parameters)
{
	ALapPhaseMOCK* testLapPhase = NewObject<ALapPhaseMOCK>();

	TestTrue(TEXT("The LapPhase should have a static mesh component after instantiating it."), testLapPhase->hasAStaticMeshComponent());

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseHasAStaticMeshTest, "ProjectR.LapPhases Tests.Unit.002: Has a static mesh associated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapPhaseHasAStaticMeshTest::RunTest(const FString& Parameters)
{
	ALapPhaseMOCK* testLapPhase = NewObject<ALapPhaseMOCK>();

	TestTrue(TEXT("The LapPhase should have a static mesh set after instantiating it."), testLapPhase->hasAStaticMeshAssociated());

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseHasPhaseWallAsRootTest, "ProjectR.LapPhases Tests.Unit.002: The phase wall is the root component", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FALapPhaseHasPhaseWallAsRootTest::RunTest(const FString& Parameters)
{
	ALapPhaseMOCK* testLapPhase = NewObject<ALapPhaseMOCK>();

	TestTrue(TEXT("The LapPhase should have its phase wall as the root component."), testLapPhase->phaseWallIsRootComponent());

	return true;
}







#endif //WITH_DEV_AUTOMATION_TESTS
