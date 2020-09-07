// Fill out your copyright notice in the Description page of Project Settings.


#include "JetTest.h"

#include "Jet.h"
#include "Mocks/JetMOCK.h"

#include "Misc/AutomationTest.h"
#include "Physics/Tests/PhysicsTestHelpers.h"
#include "Tests/AutomationCommon.h"


#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.Unit.ClassToTest.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldntBeNullWhenInstantiatedTest, "ProjectR.Unit.JetTests.ShouldntBeNullWhenInstantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldntBeNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	{
		AJet* testJet = NewObject<AJet>();
		
		TestNotNull(TEXT("The Jet shouldn't be null after instantiating it."), testJet);
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpeedIsZeroWhenInstantiatedTest, "ProjectR.Unit.JetTests.SpeedIsZeroWhenInstantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetSpeedIsZeroWhenInstantiatedTest::RunTest(const FString& Parameters)
{
	{
		AJet* testJet = NewObject<AJet>();
		
		TestTrue(TEXT("Jet speed should be zero when instantiated."), testJet->currentSpeed() == 0);
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpeedIncreasesWhenAcceleratesTest, "ProjectR.Unit.JetTests.SpeedIncreasesWhenAccelerates", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetSpeedIncreasesWhenAcceleratesTest::RunTest(const FString& Parameters)
{
	{
		AJet* testJet = NewObject<AJet>();

		const float currentSpeed = testJet->currentSpeed();

		testJet->accelerate();

		const float acceleratedSpeed = testJet->currentSpeed();
		
		TestTrue(TEXT("Speed increases when accelerates."), acceleratedSpeed > currentSpeed);
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetBrakeMakesItGoReverseWhenSpeedIsZeroTest, "ProjectR.Unit.JetTests.BrakeMakesItGoReverseWhenSpeedIsZero", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetBrakeMakesItGoReverseWhenSpeedIsZeroTest::RunTest(const FString& Parameters)
{
	{
		AJet* testJet = NewObject<AJet>();

		//another test checks that the current speed is zero when instantiated

		testJet->brake();
		
		TestTrue(TEXT("Brake is Reverse when speed is zero or negative."), testJet->currentSpeed() < 0 );
	}

	return true;
}


//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetBrakeDecreasesCurrentSpeedTest, "ProjectR.Unit.JetTests.BrakeDecreasesCurrentSpeed", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetBrakeDecreasesCurrentSpeedTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();

		const float aDesiredSpeed = 25.0f;
		
		testJet->setCurrentSpeedTo(aDesiredSpeed);

		const float currentSpeed = testJet->currentSpeed();

		testJet->brake();

		const float brakedSpeed = testJet->currentSpeed();
		
		TestTrue(TEXT("Brake decreases currentSpeed."), brakedSpeed < currentSpeed );
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSettingATopSpeedMakesItTheTopSpeedTest, "ProjectR.Unit.JetTests.SettingATopSpeedMakesItTheTopSpeed", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetSettingATopSpeedMakesItTheTopSpeedTest::RunTest(const FString& Parameters)
{
	{
		AJet* testJet = NewObject<AJet>();

		//another test checks that the current speed is zero when instantiated
		float aMaximumSpeed = 40.0f;

		testJet->setTopSpeed(aMaximumSpeed);

		float aSettedMaxSpeed = testJet->settedTopSpeed();
		
		TestTrue(TEXT("Setting a max speed should be reflected on the top speed variable."), aSettedMaxSpeed == aMaximumSpeed );
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldHaveAStaticMeshTest, "ProjectR.Unit.JetTests.ShouldHaveAStaticMesh", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldHaveAStaticMeshTest::RunTest(const FString& Parameters)
{
	{
		AJet* testJet = NewObject<AJet>();
		
		TestTrue(TEXT("The Jet static mesh shouldn't be null if it has one."), testJet->hasAStaticMesh());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMeshShouldBeTheRootComponentTest, "ProjectR.Unit.JetTests.MeshShouldBeTheRootComponent", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetMeshShouldBeTheRootComponentTest::RunTest(const FString& Parameters)
{
	{
		AJet* testJet = NewObject<AJet>();
		
		TestTrue(TEXT("The Jet static mesh should be the root component."), testJet->isMeshTheRootComponent());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldHaveGravityEnabledTest, "ProjectR.Unit.JetTests.ShouldHaveGravityEnabled", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldHaveGravityEnabledTest::RunTest(const FString& Parameters)
{
	{
		UWorld* testWorld = UWorld::CreateWorld(EWorldType::None, true);
		AJet* testJet = testWorld->SpawnActor<AJet>(AJet::StaticClass());
		
		TestTrue(TEXT("The Jet should have gravity enabled."), testJet->hasGravityEnabled());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpawnsIntoAGameWorldTest, "ProjectR.Unit.JetTests.SpawnsIntoAGameWorld", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetSpawnsIntoAGameWorldTest::RunTest(const FString& Parameters)
{
	{
		UWorld* testWorld = FPhysicsTestHelpers::GetWorld();

		AJet* testJet = testWorld->SpawnActor<AJet>(AJet::StaticClass());

		TestNotNull(TEXT("the world is not null."), testJet);
	}

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldntAffectNavigationVolumeTest, "ProjectR.Unit.JetTests.ShouldntAffectNavigationVolume", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldntAffectNavigationVolumeTest::RunTest(const FString& Parameters)
{
	{
		AJet* testJet = NewObject<AJet>();
		
		TestFalse(TEXT("The Jet shouldn't affect the navigation volume."), testJet->isAffectingNavigation());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldBeMovableTest, "ProjectR.Unit.JetTests.ShouldBeMovable", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldBeMovableTest::RunTest(const FString& Parameters)
{
	{
		UWorld* testWorld = UWorld::CreateWorld(EWorldType::None, true);
		AJet* testJet = testWorld->SpawnActor<AJet>(AJet::StaticClass());
		
		TestTrue(TEXT("The Jet should be movable when spawned into the world."), testJet->IsRootComponentMovable());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetBeInAPhysicsSceneTest, "ProjectR.Unit.JetTests.BeInAPhysicsScene", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetBeInAPhysicsSceneTest::RunTest(const FString& Parameters)
{
	{
		UWorld* testWorld = UWorld::CreateWorld(EWorldType::None, true);
		AJet* testJet = testWorld->SpawnActor<AJet>(AJet::StaticClass());
		
		TestNotNull(TEXT("The Jet should be spawned into a world with a physics scene."), testWorld->GetPhysicsScene());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldMoveWhenAccelerationAddedTest, "ProjectR.Unit.JetTests.ShouldMoveWhenAccelerationAdded", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldMoveWhenAccelerationAddedTest::RunTest(const FString& Parameters)
{
	{
		UWorld* testWorld = FPhysicsTestHelpers::GetWorld();

		AJet* testJet = testWorld->SpawnActor<AJet>(AJet::StaticClass());

		AutomationOpenMap(testWorld->GetMapName());

		FVector forceToApply {10000, 0, 0};
		FVector currentLocation = testJet->GetActorLocation();
		
		testJet->addAcceleration(forceToApply);

		testJet->Tick(0.1f);

		FVector movedLocation = testJet->GetActorLocation();

		
		
		TestFalse(TEXT("The Jet location should change after an acceleration is added (after ticking)."), movedLocation.Equals(currentLocation));
	}

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS