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

//It's nice if the prettyname follows a pattern like: Game.Unit.ClassToTest.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJetMOCKShouldntBeNullWhenInstantiatedTest, "ProjectR.Unit.JetMOCKTests.ShouldntBeNullWhenInstantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


bool FJetMOCKShouldntBeNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	
	{
		AJetMOCK* testMockJet = NewObject<AJetMOCK>();
		
		TestNotNull(TEXT("The JetMOCK shouldn't be null after instantiating it."), testMockJet);
	}

	return true;
}




//creating a world and not saving it makes the editor crash when re-running the test.
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMOCKShouldHaveGravityEnabledTest, "ProjectR.Unit.JetMOCKTests.ShouldHaveGravityEnabled", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetMOCKShouldHaveGravityEnabledTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();
		
		TestTrue(TEXT("The Jet should have gravity enabled."), testJet->hasGravityEnabled());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMOCKShouldntAffectNavigationVolumeTest, "ProjectR.Unit.JetMOCKTests.ShouldntAffectNavigationVolume", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetMOCKShouldntAffectNavigationVolumeTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();
		
		TestFalse(TEXT("The Jet shouldn't affect the navigation volume."), testJet->isAffectingNavigation());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMOCKShouldBeMovableTest, "ProjectR.Unit.JetMOCKTests.ShouldBeMovable", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetMOCKShouldBeMovableTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();
		
		TestTrue(TEXT("The Jet should be movable when spawned into the world."), testJet->IsRootComponentMovable());
	}

	return true;
}





#endif //WITH_DEV_AUTOMATION_TESTS