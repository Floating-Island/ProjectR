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



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJetMockShouldntBeNullWhenInstantiatedTest, "ProjectR.Unit.JetMockTests.JetMockShouldntBeNullWhenInstantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


bool FJetMockShouldntBeNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	
	{
		AJetMOCK* testMockJet = NewObject<AJetMOCK>();
		
		TestNotNull(TEXT("The JetMOCK shouldn't be null after instantiating it."), testMockJet);
	}

	return true;
}



//IMPLEMENT_SIMPLE_AUTOMATION_TEST(FJetMockSettingSpeedChangesSpeedToDesiredTest, "ProjectR.Unit.JetMockTests.JetMockSettingSpeedChangesSpeedToDesired", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
//
//
//bool FJetMockSettingSpeedChangesSpeedToDesiredTest::RunTest(const FString& Parameters)
//{
//	
//	{
//		AJetMOCK* testMockJet = NewObject<AJetMOCK>();
//
//		const float aDesiredSpeed = 30.0f;
//		
//		testMockJet->setCurrentSpeedTo(aDesiredSpeed);
//		
//		TestTrue(TEXT("Setting speed should change the speed to a desired one."), testMockJet->currentSpeed() == aDesiredSpeed );
//	}
//
//	return true;
//}

DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetMOCKSetVelocityToTopSpeedCommand);

bool FSpawningAJetMOCKSetVelocityToTopSpeedCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())//if not, everything would be made while the map is loading and the PIE is in progress.
	{
		return false;
	}

	UWorld* testWorld = GEditor->GetPIEWorldContext()->World();

	AJetMOCK* testJet = testWorld->SpawnActor<AJetMOCK>(AJetMOCK::StaticClass());

	testJet->setCurrentSpeedTo(testJet->settedTopSpeed());
	testJet->accelerate();

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetMOCKSpeedAgainstTopSpeedCommand, int*, tickCount, int*, tickLimit, FAutomationTestBase*, test);

bool FCheckAJetMOCKSpeedAgainstTopSpeedCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		UWorld* testWorld = GEditor->GetPIEWorldContext()->World();
		AJetMOCK* testJet = Cast<AJetMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, AJetMOCK::StaticClass()));
		if (testJet)
		{
			float currentSpeed = testJet->currentSpeed();

			*tickCount = *tickCount + 1;

			if ( (*tickCount) > (*tickLimit))
			{
				test->TestTrue(TEXT("If a jet is at top speed, it should never increase it after an acceleration is added (after ticking)."), currentSpeed <= testJet->settedTopSpeed());
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMOCKShouldntAccelerateWhenAtTopSpeedTest, "ProjectR.Unit.JetMockTests.ShouldntAccelerateWhenAtTopSpeed", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetMOCKShouldntAccelerateWhenAtTopSpeedTest::RunTest(const FString& Parameters)
{
	{
		FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");
		
		ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName))

		ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

		ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetMOCKSetVelocityToTopSpeedCommand);
		int* tickCount = new int{0};
		int tickLimit = 3;
		ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetMOCKSpeedAgainstTopSpeedCommand(tickCount, &tickLimit, this));

		ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);//no problem here.
	}

	return true;
}




#endif //WITH_DEV_AUTOMATION_TESTS