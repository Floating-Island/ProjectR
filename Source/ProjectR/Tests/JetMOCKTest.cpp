// Fill out your copyright notice in the Description page of Project Settings.


#include "JetMOCKTest.h"

#include "Mocks/JetMOCK.h"

#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "Editor.h"
#include "Kismet/GameplayStatics.h"


#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJetMOCKIsntNullWhenInstantiatedTest, "ProjectR.JetMOCK Tests.Unit.Isn't null when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


bool FJetMOCKIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{


	AJetMOCK* testMockJet = NewObject<AJetMOCK>();

	TestNotNull(TEXT("The JetMOCK shouldn't be null after instantiating it."), testMockJet);

	return true;
}









#endif //WITH_DEV_AUTOMATION_TESTS