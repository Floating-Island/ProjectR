// Fill out your copyright notice in the Description page of Project Settings.


#include "JetTest.h"

#include "Jet/Jet.h"
#include "Mocks/JetMOCK.h"

#include "Misc/AutomationTest.h"
//to be able to simulate:
#include "Tests/AutomationEditorCommon.h"
#include "Editor.h"
#include "Kismet/GameplayStatics.h"
//to be able to process inputs:
#include "GameFramework/PlayerInput.h"
#include "GameFramework/GameModeBase.h"
//used for floors:
#include "Utilities/FloorMeshActor.h"

#include "Utilities/PIESessionUtilities.h"

#if WITH_DEV_AUTOMATION_TESTS


//each one of this tests should test something of the project class that this test class references to.
//Each project class should have a test class for it. It's something kind of necessary for TDD.

//It's nice if the prettyname follows a pattern like: Game.Unit.ClassToTest.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldntBeNullWhenInstantiatedTest, "ProjectR.Unit.JetTests.ShouldntBeNullWhenInstantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldntBeNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{

	AJet* testJet = NewObject<AJet>();

	TestNotNull(TEXT("The Jet shouldn't be null after instantiating it."), testJet);


	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpeedIsZeroWhenInstantiatedTest, "ProjectR.Unit.JetTests.SpeedIsZeroWhenInstantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetSpeedIsZeroWhenInstantiatedTest::RunTest(const FString& Parameters)
{

	AJet* testJet = NewObject<AJet>();

	TestTrue(TEXT("Jet speed should be zero when instantiated."), testJet->currentSpeed() == 0);


	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldHaveAStaticMeshTest, "ProjectR.Unit.JetTests.ShouldHaveAStaticMesh", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldHaveAStaticMeshTest::RunTest(const FString& Parameters)
{

	AJetMOCK* testJet = NewObject<AJetMOCK>();

	TestTrue(TEXT("The Jet static mesh shouldn't be null if it has one."), testJet->hasAStaticMesh());


	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMeshShouldBeTheRootComponentTest, "ProjectR.Unit.JetTests.MeshShouldBeTheRootComponent", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetMeshShouldBeTheRootComponentTest::RunTest(const FString& Parameters)
{

	AJetMOCK* testJet = NewObject<AJetMOCK>();

	TestTrue(TEXT("The Jet static mesh should be the root component."), testJet->isMeshTheRootComponent());


	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldHaveGravityEnabledTest, "ProjectR.Unit.JetTests.ShouldHaveGravityEnabled", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldHaveGravityEnabledTest::RunTest(const FString& Parameters)
{

	AJetMOCK* testJet = NewObject<AJetMOCK>();

	TestTrue(TEXT("The Jet should have gravity enabled."), testJet->hasGravityEnabled());


	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldntAffectNavigationVolumeTest, "ProjectR.Unit.JetTests.ShouldntAffectNavigationVolume", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldntAffectNavigationVolumeTest::RunTest(const FString& Parameters)
{

	AJetMOCK* testJet = NewObject<AJetMOCK>();

	TestFalse(TEXT("The Jet shouldn't affect the navigation volume."), testJet->isAffectingNavigation());


	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldBeMovableTest, "ProjectR.Unit.JetTests.ShouldBeMovable", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldBeMovableTest::RunTest(const FString& Parameters)
{

	AJetMOCK* testJet = NewObject<AJetMOCK>();

	TestTrue(TEXT("The Jet should be movable when spawned into the world."), testJet->IsRootComponentMovable());


	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDefaultAccelerationIsGreaterThanZeroTest, "ProjectR.Unit.JetTests.DefaultAccelerationIsGreaterThanZero", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetDefaultAccelerationIsGreaterThanZeroTest::RunTest(const FString& Parameters)
{
	AJet* testJet = NewObject<AJet>(AJet::StaticClass());

	TestTrue(TEXT("A Jet's default acceleration should be bigger than zero."), testJet->acceleration() > 0);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItAccelerateCommand);

bool FSpawningAJetMakeItAccelerateCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())//if not, everything would be made while the map is loading and the PIE is in progress.
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();


	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	AJet* testJet = sessionUtilities.spawnJetInPIE();

	testJet->accelerate();

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetLocationCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckAJetLocationCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJet* testJet = sessionUtilities.retrieveJetFromPIE();
		if (testJet)
		{
			float currentXLocation = testJet->GetActorLocation().X;

			bool hasMoved = currentXLocation > 0;
			bool isAtOrigin = FMath::IsNearlyZero(currentXLocation, 0.1f);
			GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("Jet location: %s"), *testJet->GetActorLocation().ToString()));
			GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("Jet %s at origin (0,0,0)"), *FString(isAtOrigin? "is":"isn't")));
			if (hasMoved && !isAtOrigin)//it would be better to align the ship first and then check against it's forward vector. We have to be careful of gravity in this test.
			{
				test->TestTrue(TEXT("The Jet X location should increase after an acceleration is added (after ticking)."), hasMoved && !isAtOrigin);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			++aTickCount;

			if (aTickCount > aTickLimit)
			{
				test->TestFalse(TEXT("Tick limit reached for this test. The Jet X Location never changed from zero."), aTickCount > aTickLimit);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldMoveForwardWhenAcceleratedTest, "ProjectR.Unit.JetTests.ShouldMoveForwardWhenAccelerated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldMoveForwardWhenAcceleratedTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItAccelerateCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetLocationCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetSpeedIncreaseCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckAJetSpeedIncreaseCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJet* testJet = sessionUtilities.retrieveJetFromPIE();
		if (testJet)
		{
			float currentSpeed = testJet->currentSpeed();

			FVector jetForwardDirection = testJet->GetActorForwardVector();
			bool isMovingForwards = testJet->GetVelocity().ProjectOnTo(jetForwardDirection).GetSignVector() == jetForwardDirection.GetSignVector();
			bool isIdle = FMath::IsNearlyZero(currentSpeed, 0.1f);

			if (isMovingForwards && !isIdle)
			{
				test->TestTrue(TEXT("The Jet speed should increase after accelerating (after ticking)."), isMovingForwards && !isIdle);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}

			++aTickCount;

			if (aTickCount > aTickLimit)
			{
				test->TestFalse(TEXT("Tick limit reached for this test. The Jet speed never changed from zero."), aTickCount > aTickLimit);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpeedIncreasesWhenAcceleratesTest, "ProjectR.Unit.JetTests.SpeedIncreasesWhenAccelerates", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetSpeedIncreasesWhenAcceleratesTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItAccelerateCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedIncreaseCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDefaultBrakeValueIsGreaterThanZeroTest, "ProjectR.Unit.JetTests.DefaultBrakeValueIsGreaterThanZero", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetDefaultBrakeValueIsGreaterThanZeroTest::RunTest(const FString& Parameters)
{
	AJet* testJet = NewObject<AJet>(AJet::StaticClass());

	TestTrue(TEXT("A Jet's default brake value should be bigger than zero."), testJet->brakeValue() > 0);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItBrakeCommand);

bool FSpawningAJetMakeItBrakeCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	AJet* testJet = sessionUtilities.spawnJetInPIE();

	testJet->brake();

	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetVelocityDecreaseCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckAJetVelocityDecreaseCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJet* testJet = sessionUtilities.retrieveJetFromPIE();
		if (testJet)
		{
			float currentSpeed = testJet->currentSpeed();
			bool isIdle = FMath::IsNearlyZero(currentSpeed, 0.1f);
			FVector jetForwardDirection = testJet->GetActorForwardVector();
			bool isMovingBackwards = testJet->GetVelocity().ProjectOnTo(jetForwardDirection).GetSignVector() != jetForwardDirection.GetSignVector();
			

			if (isMovingBackwards && !isIdle)
			{
				test->TestTrue(TEXT("The Jet velocity should be negative after a brake (after ticking) from idle."), isMovingBackwards && !isIdle);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			++aTickCount;

			if (aTickCount > aTickLimit)
			{
				test->TestFalse(TEXT("Tick limit reached for this test. The Jet velocity never changed from zero."), aTickCount > aTickLimit);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetVelocityNegativeWhenBrakesTest, "ProjectR.Unit.JetTests.VelocityNegativeWhenBrakes", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetVelocityNegativeWhenBrakesTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItBrakeCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetVelocityDecreaseCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDefaultTopSpeedIsGreaterThanZeroTest, "ProjectR.Unit.JetTests.DefaultTopSpeedIsGreaterThanZero", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetDefaultTopSpeedIsGreaterThanZeroTest::RunTest(const FString& Parameters)
{
	AJet* testJet = NewObject<AJet>(AJet::StaticClass());

	TestTrue(TEXT("A Jet's default top speed should be bigger than zero."), testJet->settedTopSpeed() > 0);

	return true;
}






//uses a jet mock
DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetSetVelocityToTopSpeedCommand);

bool FSpawningAJetSetVelocityToTopSpeedCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	AJetMOCK* testJet = sessionUtilities.spawnJetMOCKInPIE();

	testJet->setCurrentSpeedTo(testJet->settedTopSpeed());
	testJet->accelerate();

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetSpeedAgainstTopSpeedCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckAJetSpeedAgainstTopSpeedCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJetMOCK* testJet = sessionUtilities.retrieveJetMOCKFromPIE();
		if (testJet)
		{
			float currentSpeed = testJet->currentSpeed();
			bool isAtTopSpeed = FMath::IsNearlyEqual(currentSpeed, testJet->settedTopSpeed(), 1.4f);
			GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("Jet location: %s"), *testJet->GetActorLocation().ToString()));
			GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("Jet location: %f"), currentSpeed));
			GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("Jet %s at currentSpeed"), *FString(isAtTopSpeed? "is":"isn't")));
			++aTickCount;

			if (aTickCount > aTickLimit)
			{
				test->TestTrue(TEXT("If a jet is at top speed, it should never increase it after an acceleration is added (after ticking)."), isAtTopSpeed);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldntAccelerateWhenAtTopSpeedTest, "ProjectR.Unit.JetTests.ShouldntAccelerateWhenAtTopSpeed", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldntAccelerateWhenAtTopSpeedTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetSetVelocityToTopSpeedCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedAgainstTopSpeedCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItSteerRightCommand);

bool FSpawningAJetMakeItSteerRightCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	AJet* testJet = sessionUtilities.spawnJetInPIE();

	float direction = 1;//1 is right, -1 is left...

	testJet->steer(direction);

	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetRotatedYawCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckAJetRotatedYawCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJet* testJet = sessionUtilities.retrieveJetFromPIE();
		if (testJet)
		{
			float currentZRotation = testJet->GetActorRotation().Yaw;
			bool hasSteeredRight = currentZRotation > 0;
			bool isMinimalSteering = FMath::IsNearlyZero(currentZRotation, 0.1f);

			if (hasSteeredRight && !isMinimalSteering)
			{
				test->TestTrue(TEXT("The Jet yaw rotation (around Z axis) should be greater than zero after steering right (after ticking)."), hasSteeredRight && !isMinimalSteering);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			++aTickCount;

			if (aTickCount > aTickLimit)
			{
				test->TestFalse(TEXT("Tick limit reached for this test. The Jet yaw rotation (around Z axis) never changed from zero."), aTickCount > aTickLimit);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldRotateYawRightWhenSteeringRightTest, "ProjectR.Unit.JetTests.ShouldRotateYawRightWhenSteeringRight", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldRotateYawRightWhenSteeringRightTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItSteerRightCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetRotatedYawCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDefaultSteerForceIsGreaterThanZeroTest, "ProjectR.Unit.JetTests.DefaultSteerForceIsGreaterThanZero", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetDefaultSteerForceIsGreaterThanZeroTest::RunTest(const FString& Parameters)
{
	AJet* testJet = NewObject<AJet>(AJet::StaticClass());

	TestTrue(TEXT("A Jet's default steer force should be bigger than zero."), testJet->steerForce() > 0);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressAccelerationKeyCommand);

bool FSpawningAJetPressAccelerationKeyCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	AJet* testJet = sessionUtilities.spawnJetInPIE();

	sessionUtilities.processLocalPlayerInputFrom(FName(TEXT("AccelerateAction")));

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetAcceleratesWhenPressingAccelerationKeyTest, "ProjectR.Unit.JetTests.AcceleratesWhenPressingAccelerationKey", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetAcceleratesWhenPressingAccelerationKeyTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressAccelerationKeyCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedIncreaseCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressSteerRightKeyCommand);

bool FSpawningAJetPressSteerRightKeyCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	AJet* testJet = sessionUtilities.spawnJetInPIE();

	sessionUtilities.processLocalPlayerInputFrom(FName(TEXT("SteerAction")));

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldMoveRightWhenPressingSteerRightKeyTest, "ProjectR.Unit.JetTests.ShouldMoveRightWhenPressingSteerRightKey", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldMoveRightWhenPressingSteerRightKeyTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressSteerRightKeyCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetRotatedYawCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressBrakeKeyCommand);

bool FSpawningAJetPressBrakeKeyCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	AJet* testJet = sessionUtilities.spawnJetInPIE();

	sessionUtilities.processLocalPlayerInputFrom(FName(TEXT("BrakeAction")));

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetBrakesWhenPressingBrakeKeyTest, "ProjectR.Unit.JetTests.BrakesWhenPressingBrakeKey", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetBrakesWhenPressingBrakeKeyTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressBrakeKeyCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetVelocityDecreaseCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldHaveASpringArmTest, "ProjectR.Unit.JetTests.ShouldHaveASpringArm", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldHaveASpringArmTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();

		TestTrue(TEXT("The Jet should have a spring arm."), testJet->hasASprinArm());
	}

	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldHaveASpringArmAttachedToRootComponentTest, "ProjectR.Unit.JetTests.ShouldHaveASpringArmAttachedToRootComponent", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldHaveASpringArmAttachedToRootComponentTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();

		TestTrue(TEXT("The Jet should have a spring arm attached to the root component."), testJet->isSpringArmAttachedToRoot());
	}

	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldHaveACameraTest, "ProjectR.Unit.JetTests.ShouldHaveACamera", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldHaveACameraTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();

		TestTrue(TEXT("The Jet should have a camera."), testJet->HasCameraComponent());
	}

	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldHaveACameraAttachedToSpringArmTest, "ProjectR.Unit.JetTests.ShouldHaveACameraAttachedToSpringArm", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldHaveACameraAttachedToSpringArmTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();

		TestTrue(TEXT("The Jet should have a camera attached to a springArm."), testJet->isCameraAttachedToSpringArm());
	}

	return true;
}



////uses a MOCK
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpringArmShouldUseAbsoluteRotationTest, "ProjectR.Unit.JetTests.SpringArmShouldUseAbsoluteRotation", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
//
//bool FAJetSpringArmShouldUseAbsoluteRotationTest::RunTest(const FString& Parameters)
//{
//	{
//		AJetMOCK* testJet = NewObject<AJetMOCK>();
//
//		TestTrue(TEXT("The Jet spring arm should use absolute rotation."), testJet->usesAbsoluteRotation());//change to use the relative yaw
//	}
//
//	return true;
//}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetSnapedToFloorCommand);

bool FSpawningAJetSnapedToFloorCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	AFloorMeshActor* meshActor = sessionUtilities.spawnFloorMeshActorInPIE();

	FVector spawnLocation = meshActor->GetActorLocation() + FVector(0, 0, 1000);

	AJetMOCK* testJet = sessionUtilities.spawnJetMOCKInPIE(spawnLocation);

	GEditor->SnapObjectTo(FActorOrComponent(testJet), true, true, true, false, FActorOrComponent(meshActor));

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetZLocationCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckAJetZLocationCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJetMOCK* testJet = sessionUtilities.retrieveJetMOCKFromPIE();
		if (testJet)
		{
			float currentZVelocity = testJet->getZVelocity();

			bool isBeingLifted = currentZVelocity > 0;
			bool isMinimalLifting = FMath::IsNearlyZero(currentZVelocity, 0.1f);

			if (isBeingLifted && !isMinimalLifting)
			{
				test->TestTrue(TEXT("The Jet Z veocity should increase due to anti-gravity activation near floor."), isBeingLifted && !isMinimalLifting);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			++aTickCount;

			if (aTickCount > aTickLimit)
			{
				test->TestFalse(TEXT("Tick limit reached for this test. The Jet never lifted from the ground."), aTickCount > aTickLimit);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}

//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetGetsUpwardsImpulseFromAntiGravityOnFloorTest, "ProjectR.Unit.JetTests.GetsUpwardsImpulseFromAntiGravityOnFloor", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetGetsUpwardsImpulseFromAntiGravityOnFloorTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetSnapedToFloorCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetZLocationCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotateAndAccelerateCommand);

bool FSpawningAJetRotateAndAccelerateCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();


	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	AJet* testJet = sessionUtilities.spawnJetInPIE();

	float yawValue = 50;
	testJet->SetActorRotation(FRotator(0, yawValue, 0));
	testJet->accelerate();

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetLocationCoincidentToForwardVectorCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckAJetLocationCoincidentToForwardVectorCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJet* testJet = sessionUtilities.retrieveJetFromPIE();
		if (testJet)
		{
			FVector currentLocation = testJet->GetActorLocation();
			FVector jetForwardVector = testJet->GetActorForwardVector();

			bool hasMoved = !FMath::IsNearlyZero(FVector::Distance(currentLocation, FVector(0)), 0.1f);
			bool locationIsAlignedToForwardVector = FVector::Coincident(currentLocation.GetSafeNormal2D(), jetForwardVector.GetSafeNormal2D());

			if (hasMoved && locationIsAlignedToForwardVector)//it would be better to align the ship first and then check against it's forward vector. We have to be careful of gravity in this test.
			{
				test->TestTrue(TEXT("The Jet should accelerate in the direction of it's forward vector after being rotated."), hasMoved && locationIsAlignedToForwardVector);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			++aTickCount;

			if (aTickCount > aTickLimit)
			{
				test->TestFalse(TEXT("Tick limit reached for this test. The Jet acceleration wasn't aligned to it's forward vector."), aTickCount > aTickLimit);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldAccelerateAlongItsForwardVectorWhenAcceleratedAfterRotationTest, "ProjectR.Unit.JetTests.ShouldAccelerateAlongItsForwardVectorWhenAcceleratedAfterRotation", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldAccelerateAlongItsForwardVectorWhenAcceleratedAfterRotationTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotateAndAccelerateCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetLocationCoincidentToForwardVectorCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotateAndBrakeCommand);

bool FSpawningAJetRotateAndBrakeCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	PIESessionUtilities sessionUtilities = PIESessionUtilities();


	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	AJet* testJet = sessionUtilities.spawnJetInPIE();

	float yawValue = 50;
	testJet->SetActorRotation(FRotator(0, yawValue, 0));
	testJet->brake();

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetLocationParallelToForwardVectorCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckAJetLocationParallelToForwardVectorCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJet* testJet = sessionUtilities.retrieveJetFromPIE();
		if (testJet)
		{
			FVector currentLocation = testJet->GetActorLocation();
			FVector jetBackwardsVector = -testJet->GetActorForwardVector();//notice the '-'. It's the forward vector negated.

			bool hasMoved = !FMath::IsNearlyZero(FVector::Distance(currentLocation, jetBackwardsVector), 0.1f);
			bool locationIsAlignedToBackwardsVector = FVector::Coincident(currentLocation.GetSafeNormal2D(), jetBackwardsVector.GetSafeNormal2D());

			if (hasMoved && locationIsAlignedToBackwardsVector)
			{
				test->TestTrue(TEXT("The Jet should brake contrary to the direction of it's forward vector after being rotated."), hasMoved && locationIsAlignedToBackwardsVector);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			++aTickCount;

			if (aTickCount > aTickLimit)
			{
				test->TestFalse(TEXT("Tick limit reached for this test. The Jet acceleration wasn't aligned to it's forward vector."), aTickCount > aTickLimit);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldBrakeAlongItsBackwardsVectorWhileRotatedTest, "ProjectR.Unit.JetTests.ShouldBrakeAlongItsBackwardsVectorWhileRotated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldBrakeAlongItsBackwardsVectorWhileRotatedTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotateAndBrakeCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetLocationParallelToForwardVectorCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetAccelerateAndSteerRightCommand);

bool FSpawningAJetAccelerateAndSteerRightCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	UWorld* testWorld = sessionUtilities.currentPIEWorld();


	AFloorMeshActor* meshActor = sessionUtilities.spawnFloorMeshActorInPIE();

	FVector spawnLocation = meshActor->GetActorLocation() + FVector(0, 0, 1000);

	AJetMOCK* testJet = sessionUtilities.spawnJetMOCKInPIE(spawnLocation);

	GEditor->SnapObjectTo(FActorOrComponent(testJet), true, true, true, false, FActorOrComponent(meshActor));
	
	float direction = 1;//1 is right, -1 is left...
	testJet->accelerate();
	testJet->steer(direction);

	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetUpdatedVelocityWhenAfterSteeringCommand, int, aTickCount, int, aTickLimit,FVector, previousForwardVector, FAutomationTestBase*, test);

bool FCheckAJetUpdatedVelocityWhenAfterSteeringCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJet* testJet = sessionUtilities.retrieveJetFromPIE();
		if (testJet)
		{
			++aTickCount;

			FVector currentVelocity = testJet->GetVelocity();
			FVector jetForwardsVector = testJet->GetActorForwardVector();
			bool speedNearlyZero = FMath::IsNearlyZero(testJet->currentSpeed(), 0.1f);
			bool velocityAlignedToPreviousForwardVector = FVector::Coincident(currentVelocity.GetSafeNormal2D(), previousForwardVector.GetSafeNormal2D());
			
			if (aTickCount > aTickLimit)
			{
				test->TestTrue(TEXT("The Jet should update it's velocity to match the direction of the forward vector after steering."), !speedNearlyZero && velocityAlignedToPreviousForwardVector);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			previousForwardVector = jetForwardsVector;
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldUpdateVelocityDirectionAfterSteeringTest, "ProjectR.Unit.JetTests.ShouldUpdateVelocityDirectionAfterSteering", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldUpdateVelocityDirectionAfterSteeringTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetAccelerateAndSteerRightCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetUpdatedVelocityWhenAfterSteeringCommand(tickCount, tickLimit, FVector(0), this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetBrakeAndSteerRightCommand);

bool FSpawningAJetBrakeAndSteerRightCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	AJetMOCK* testJet = sessionUtilities.spawnJetMOCKInPIE();
	
	float direction = 1;//1 is right, -1 is left going forwards
	testJet->brake();
	testJet->steer(direction);

	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetInvertSteeringWhenInReverseCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckAJetInvertSteeringWhenInReverseCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJet* testJet = sessionUtilities.retrieveJetFromPIE();
		if (testJet)
		{
			++aTickCount;

			bool ismovingRight = testJet->GetVelocity().Y < 0;//clockwise is right when going forwards. When in reverse, it should go counterclockwise.
			bool isMinimalSteering = FMath::IsNearlyZero(testJet->GetActorRotation().Yaw, 0.1f);
			bool speedNearlyZero = FMath::IsNearlyZero(testJet->currentSpeed(), 0.1f);
			FVector jetForwardDirection = testJet->GetActorForwardVector();
			bool isMovingBackwards = testJet->GetVelocity().ProjectOnTo(jetForwardDirection).GetSignVector().X != jetForwardDirection.GetSignVector().X;

			if (!speedNearlyZero && !isMinimalSteering && ismovingRight && isMovingBackwards)
			{
				test->TestTrue(TEXT("The Jet should steer right counterclockwise if it's in reverse."), !speedNearlyZero && !isMinimalSteering && ismovingRight && isMovingBackwards);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			++aTickCount;

			if (aTickCount > aTickLimit)
			{
				test->TestFalse(TEXT("Tick limit reached for this test. The Jet didn't steer right counterclockwise in reverse."), aTickCount > aTickLimit);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldInvertSteeringWhenInReverseTest, "ProjectR.Unit.JetTests.ShouldInvertSteeringWhenInReverse", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldInvertSteeringWhenInReverseTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetBrakeAndSteerRightCommand);
	int tickCount = 0;
	int tickLimit = 4;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetInvertSteeringWhenInReverseCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}

//RECHECK TESTS, look a way to simplify them and look why sometimes they fail. Also, create the tick function and then move it to a new component.


#endif //WITH_DEV_AUTOMATION_TESTS