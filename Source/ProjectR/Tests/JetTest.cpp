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

//It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
//TestName should express what you expect from a test given a scenario.
//Pay attention to the automation flags because they're needed to run the tests without UI errors.


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetIsntNullWhenInstantiatedTest, "ProjectR.Jet Tests.Unit.000: Isn't null when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetIsntNullWhenInstantiatedTest::RunTest(const FString& Parameters)
{

	AJet* testJet = NewObject<AJet>();

	TestNotNull(TEXT("The Jet shouldn't be null after instantiating it."), testJet);


	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpeedIsZeroWhenInstantiatedTest, "ProjectR.Jet Tests.Unit.001: Speed is zero when instantiated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetSpeedIsZeroWhenInstantiatedTest::RunTest(const FString& Parameters)
{

	AJet* testJet = NewObject<AJet>();

	TestTrue(TEXT("Jet speed should be zero when instantiated."), testJet->currentSpeed() == 0);


	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetHasAStaticMeshTest, "ProjectR.Jet Tests.Unit.002: Has a static mesh as physics mesh", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetHasAStaticMeshTest::RunTest(const FString& Parameters)
{

	AJetMOCK* testJet = NewObject<AJetMOCK>();

	TestTrue(TEXT("The Jet physics mesh shouldn't be null if it has one."), testJet->hasAPhysicsMesh());


	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMeshIsTheRootComponentTest, "ProjectR.Jet Tests.Unit.003: Mesh is the root component", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetMeshIsTheRootComponentTest::RunTest(const FString& Parameters)
{

	AJetMOCK* testJet = NewObject<AJetMOCK>();

	TestTrue(TEXT("The Jet physics mesh should be the root component."), testJet->isPhysicsMeshTheRootComponent());


	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetHasGravityEnabledTest, "ProjectR.Jet Tests.Unit.004: Has gravity enabled", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetHasGravityEnabledTest::RunTest(const FString& Parameters)
{

	AJetMOCK* testJet = NewObject<AJetMOCK>();

	TestTrue(TEXT("The Jet should have gravity enabled."), testJet->hasGravityEnabled());


	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDoesntAffectNavigationVolumeTest, "ProjectR.Jet Tests.Unit.005: Doesn't affect navigation volume", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetDoesntAffectNavigationVolumeTest::RunTest(const FString& Parameters)
{

	AJetMOCK* testJet = NewObject<AJetMOCK>();

	TestFalse(TEXT("The Jet shouldn't affect the navigation volume."), testJet->isAffectingNavigation());


	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetIsMovableTest, "ProjectR.Jet Tests.Unit.006: Is movable", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetIsMovableTest::RunTest(const FString& Parameters)
{

	AJetMOCK* testJet = NewObject<AJetMOCK>();

	TestTrue(TEXT("The Jet should be movable when spawned into the world."), testJet->IsRootComponentMovable());


	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDefaultAccelerationIsGreaterThanZeroTest, "ProjectR.Jet Tests.Unit.007: Default acceleration is greater than zero", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

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

	AJet* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJet>();

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
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		if (testJet)
		{
			float currentXLocation = testJet->GetActorLocation().X;

			bool hasMoved = currentXLocation > 0;
			bool isAtOrigin = FMath::IsNearlyZero(currentXLocation, 0.1f);


			UE_LOG(LogTemp, Log, TEXT("Jet location: %s."), *testJet->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet %s moved."), *FString(hasMoved ? "is" : "isn't"));
			UE_LOG(LogTemp, Log, TEXT("Jet %s at origin (0,0,0)."), *FString(isAtOrigin ? "is" : "isn't"));
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



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMovesForwardWhenAcceleratedTest, "ProjectR.Jet Tests.Unit.008: Moves forward when accelerated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetMovesForwardWhenAcceleratedTest::RunTest(const FString& Parameters)
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
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		if (testJet)
		{
			float currentSpeed = testJet->currentSpeed();

			FVector jetForwardDirection = testJet->GetActorForwardVector();
			bool isMovingForwards = testJet->GetVelocity().ProjectOnTo(jetForwardDirection).GetSignVector() == jetForwardDirection.GetSignVector();
			bool isIdle = FMath::IsNearlyZero(currentSpeed, 0.1f);

			UE_LOG(LogTemp, Log, TEXT("Jet forward vector: %s"), *jetForwardDirection.ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet velocity: %s"), *testJet->GetVelocity().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet velocity projection on forward vector: %s"), *testJet->GetVelocity().ProjectOnTo(jetForwardDirection).ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet velocity projection sign: %s"), *testJet->GetVelocity().ProjectOnTo(jetForwardDirection).GetSignVector().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet forward vector sign: %s"), *jetForwardDirection.GetSignVector().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet %s moving forwards."), *FString(isMovingForwards ? "is" : "isn't"));
			UE_LOG(LogTemp, Log, TEXT("Jet %s idle."), *FString(isIdle ? "is" : "isn't"));

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


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpeedIncreasesWhenAcceleratesTest, "ProjectR.Jet Tests.Unit.009: Speed increases when accelerates", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

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



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDefaultBrakeValueIsGreaterThanZeroTest, "ProjectR.Jet Tests.Unit.010: Default brake value is greater than zero", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

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

	AJet* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJet>();

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
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		if (testJet)
		{
			float currentSpeed = testJet->currentSpeed();
			bool isIdle = FMath::IsNearlyZero(currentSpeed, 0.1f);
			FVector jetForwardDirection = testJet->GetActorForwardVector();
			bool isMovingBackwards = testJet->GetVelocity().ProjectOnTo(jetForwardDirection).GetSignVector() != jetForwardDirection.GetSignVector();

			UE_LOG(LogTemp, Log, TEXT("Jet forward vector: %s"), *jetForwardDirection.ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet velocity: %s"), *testJet->GetVelocity().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet velocity projection on forward vector: %s"), *testJet->GetVelocity().ProjectOnTo(jetForwardDirection).ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet velocity projection sign: %s"), *testJet->GetVelocity().ProjectOnTo(jetForwardDirection).GetSignVector().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet forward vector sign: %s"), *jetForwardDirection.GetSignVector().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet %s moving backwards."), *FString(isMovingBackwards ? "is" : "isn't"));
			UE_LOG(LogTemp, Log, TEXT("Jet %s idle."), *FString(isIdle ? "is" : "isn't"));

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


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetVelocityNegativeWhenBrakesTest, "ProjectR.Jet Tests.Unit.011: Velocity is negative when brakes", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

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



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDefaultTopSpeedIsGreaterThanZeroTest, "ProjectR.Jet Tests.Unit.012: Default top speed is greater than zero", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

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

	AJetMOCK* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJetMOCK>();

	testJet->setCurrentXVelocityTo(testJet->settedTopSpeed());
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
		AJetMOCK* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJetMOCK>();
		if (testJet)
		{
			float currentSpeed = testJet->currentSpeed();
			bool isAtTopSpeed = FMath::IsNearlyEqual(currentSpeed, testJet->settedTopSpeed(), 2.0f);
			UE_LOG(LogTemp, Log, TEXT("Jet location: %s"), *testJet->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet speed: %f"), currentSpeed);
			UE_LOG(LogTemp, Log, TEXT("Jet top speed: %f"), testJet->settedTopSpeed());
			UE_LOG(LogTemp, Log, TEXT("Jet %s at currentSpeed"), *FString(isAtTopSpeed ? "is" : "isn't"));
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


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDoesntAccelerateWhenAtTopSpeedTest, "ProjectR.Jet Tests.Unit.013: Doesn't accelerate when at top speed", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetDoesntAccelerateWhenAtTopSpeedTest::RunTest(const FString& Parameters)
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

	AJetMOCK* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJetMOCK>();

	testJet->setCurrentXVelocityTo(10000);//we should set the speed to 1000 first so the jet is able to steer.
	testJet->steerRightEveryTick();

	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetRotatedYawCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckAJetRotatedYawCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJetMOCK* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJetMOCK>();
		if (testJet)
		{
			float currentZRotation = testJet->GetActorRotation().Yaw;
			bool hasSteeredRight = currentZRotation > 0;
			bool isMinimalSteering = FMath::IsNearlyZero(currentZRotation, 0.1f);

			UE_LOG(LogTemp, Log, TEXT("Jet rotation vector: %s"), *testJet->GetActorRotation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet %s steered right."), *FString(hasSteeredRight ? "has" : "hasn't"));
			UE_LOG(LogTemp, Log, TEXT("Jet %s made a minimal steering."), *FString(isMinimalSteering ? "has" : "hasn't"));

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


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetRotatesYawRightWhenSteeringRightTest, "ProjectR.Jet Tests.Unit.014: Rotates yaw right when steering right", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetRotatesYawRightWhenSteeringRightTest::RunTest(const FString& Parameters)
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



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetDefaultSteerRadiusIsGreaterThanZeroTest, "ProjectR.Jet Tests.Unit.015: Default steer radius is greater than zero", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetDefaultSteerRadiusIsGreaterThanZeroTest::RunTest(const FString& Parameters)
{
	AJet* testJet = NewObject<AJet>(AJet::StaticClass());

	TestTrue(TEXT("A Jet's default steer radius should be bigger than zero."), testJet->steerRadius() > 0);

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

	AJet* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJet>();

	sessionUtilities.processLocalPlayerInputFrom(FName(TEXT("AccelerateAction")));

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetAcceleratesWhenPressingAccelerationKeyTest, "ProjectR.Jet Tests.Unit.016: Accelerates when pressing acceleration key", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

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

	AJetMOCK* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJetMOCK>();

	testJet->setCurrentXVelocityTo(10000);//we should set the speed to 1 first so the jet is able to steer.
	sessionUtilities.processLocalPlayerInputFrom(FName(TEXT("SteerAction")));

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMovesRightWhenPressingSteerRightKeyTest, "ProjectR.Jet Tests.Unit.017: Moves right when pressing steer right key", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetMovesRightWhenPressingSteerRightKeyTest::RunTest(const FString& Parameters)
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

	AJet* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJet>();

	sessionUtilities.processLocalPlayerInputFrom(FName(TEXT("BrakeAction")));

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetBrakesWhenPressingBrakeKeyTest, "ProjectR.Jet Tests.Unit.018: Brakes when pressing brake key", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

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
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetHasASpringArmTest, "ProjectR.Jet Tests.Unit.019: Has a spring arm", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetHasASpringArmTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();

		TestTrue(TEXT("The Jet should have a spring arm."), testJet->hasASprinArm());
	}

	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpringArmIsAttachedToRootComponentTest, "ProjectR.Jet Tests.Unit.020: Spring arm is attached to root component", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetSpringArmIsAttachedToRootComponentTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();

		TestTrue(TEXT("The Jet should have a spring arm attached to the root component."), testJet->isSpringArmAttachedToRoot());
	}

	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetHasACameraTest, "ProjectR.Jet Tests.Unit.021: Has a camera", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetHasACameraTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();

		TestTrue(TEXT("The Jet should have a camera."), testJet->HasCameraComponent());
	}

	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetCameraIsAttachedToSpringArmTest, "ProjectR.Jet Tests.Unit.022: Camera is attached to spring arm", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetCameraIsAttachedToSpringArmTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();

		TestTrue(TEXT("The Jet should have a camera attached to a springArm."), testJet->isCameraAttachedToSpringArm());
	}

	return true;
}



////uses a MOCK
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpringArmShouldUseAbsoluteRotationTest, "ProjectR.Jet Tests.Unit.SpringArmShouldUseAbsoluteRotation", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
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

	AFloorMeshActor* meshActor = sessionUtilities.spawnInPIEAnInstanceOf<AFloorMeshActor>();

	FVector spawnLocation = meshActor->GetActorLocation() + FVector(0, 0, 1000);

	AJetMOCK* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJetMOCK>(spawnLocation);

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
		AJetMOCK* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJetMOCK>();
		if (testJet)
		{
			float currentZVelocity = testJet->getZVelocity();

			bool isBeingLifted = currentZVelocity > 0;
			bool isMinimalLifting = FMath::IsNearlyZero(currentZVelocity, 0.1f);

			UE_LOG(LogTemp, Log, TEXT("Jet velocity: %s"), *testJet->GetVelocity().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet %s being lifted."), *FString(isBeingLifted ? "is" : "isn't"));
			UE_LOG(LogTemp, Log, TEXT("Jet %s made a minimal lifting."), *FString(isMinimalLifting ? "has" : "hasn't"));

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
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetGetsUpwardsImpulseFromAntiGravityOnFloorTest, "ProjectR.Jet Tests.Integration.023: Gets upwards impulse from anti-gravity on floor", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

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

	AJet* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJet>();

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
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		if (testJet)
		{
			FVector currentLocation = testJet->GetActorLocation();
			FVector jetForwardVector = testJet->GetActorForwardVector();

			bool hasMoved = !FMath::IsNearlyZero(FVector::Distance(currentLocation, FVector(0)), 0.1f);
			bool locationIsAlignedToForwardVector = FVector::Coincident(currentLocation.GetSafeNormal2D(), jetForwardVector.GetSafeNormal2D());

			UE_LOG(LogTemp, Log, TEXT("Jet forward vector: %s"), *jetForwardVector.ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet location: %s"), *currentLocation.ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet location up vector on XY: %s"), *currentLocation.GetSafeNormal2D().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet forward vector up vector on XY: %s"), *jetForwardVector.GetSafeNormal2D().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet %s moved."), *FString(hasMoved ? "has" : "hasn't"));
			UE_LOG(LogTemp, Log, TEXT("Jet location %s aligned to forward vector."), *FString(locationIsAlignedToForwardVector ? "is" : "isn't"));

			if (hasMoved && locationIsAlignedToForwardVector)//We have to be careful of gravity in this test. That's why a up vector on XY is used.
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



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetAcceleratesAlongItsForwardVectorWhenAcceleratedAfterRotationTest, "ProjectR.Jet Tests.Unit.024: Accelerates along its forward vector when accelerated after being rotated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetAcceleratesAlongItsForwardVectorWhenAcceleratedAfterRotationTest::RunTest(const FString& Parameters)
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

	AJet* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJet>();

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
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		if (testJet)
		{
			FVector currentLocation = testJet->GetActorLocation();
			FVector jetBackwardsVector = -testJet->GetActorForwardVector();//notice the '-'. It's the forward vector negated.

			bool hasMoved = !FMath::IsNearlyZero(FVector::Distance(currentLocation, jetBackwardsVector), 0.1f);
			bool locationIsAlignedToBackwardsVector = FVector::Coincident(currentLocation.GetSafeNormal2D(), jetBackwardsVector.GetSafeNormal2D());

			UE_LOG(LogTemp, Log, TEXT("Jet backwards vector: %s"), *jetBackwardsVector.ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet location: %s"), *currentLocation.ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet location up vector on XY: %s"), *currentLocation.GetSafeNormal2D().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet backwards vector up vector on XY: %s"), *jetBackwardsVector.GetSafeNormal2D().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet %s moved."), *FString(hasMoved ? "has" : "hasn't"));
			UE_LOG(LogTemp, Log, TEXT("Jet location %s aligned to backwards vector."), *FString(locationIsAlignedToBackwardsVector ? "is" : "isn't"));

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



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetBrakesAlongItsBackwardsVectorWhileRotatedTest, "ProjectR.Jet Tests.Unit.025: Brakes along its backwards vector after being rotated", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetBrakesAlongItsBackwardsVectorWhileRotatedTest::RunTest(const FString& Parameters)
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
//
//
//
//
//
//
//DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetAccelerateAndSteerRightCommand);
//
//bool FSpawningAJetAccelerateAndSteerRightCommand::Update()
//{
//	if (!GEditor->IsPlayingSessionInEditor())
//	{
//		return false;
//	}
//	PIESessionUtilities sessionUtilities = PIESessionUtilities();
//
//	UWorld* testWorld = sessionUtilities.currentPIEWorld();
//
//	AJetMOCK* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJetMOCK>();
//
//	testJet->setCurrentXVelocityTo(10000);//we go forward and then steer.
//	testJet->steerRightEveryTick();
//
//	return true;
//}
//
//
//DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetUpdatedVelocityWhenAfterSteeringCommand, int, aTickCount, int, aTickLimit, FVector, previousForwardVector, FAutomationTestBase*, test);
//
//bool FCheckAJetUpdatedVelocityWhenAfterSteeringCommand::Update()
//{
//	if (GEditor->IsPlayingSessionInEditor())
//	{
//		PIESessionUtilities sessionUtilities = PIESessionUtilities();
//		UWorld* testWorld = sessionUtilities.currentPIEWorld();
//		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
//		if (testJet)
//		{
//
//			FVector currentVelocity = testJet->velocityProjectionOnFloor();
//			FVector jetForwardsVector = testJet->ForwardProjectionOnFloor();
//			bool speedNearlyZero = FMath::IsNearlyZero(testJet->currentSpeed(), 0.1f);
//			bool velocityAlignedToPreviousForwardVector = FVector::Coincident(currentVelocity, previousForwardVector);
//
//			UE_LOG(LogTemp, Log, TEXT("Tick: %d"), aTickCount);
//			UE_LOG(LogTemp, Log, TEXT("Jet previous forward vector: %s"), *previousForwardVector.ToString());
//			UE_LOG(LogTemp, Log, TEXT("Jet current forward vector: %s"), *jetForwardsVector.ToString());
//			UE_LOG(LogTemp, Log, TEXT("Jet velocity: %s"), *currentVelocity.ToString());
//			UE_LOG(LogTemp, Log, TEXT("Jet speed %s nearly zero."), *FString(speedNearlyZero ? "is" : "isn't"));
//			UE_LOG(LogTemp, Log, TEXT("Jet velocity %s aligned to previous forward vector."), *FString(velocityAlignedToPreviousForwardVector ? "is" : "isn't"));
//			UE_LOG(LogTemp, Log, TEXT("End of tick."));
//
//			++aTickCount;
//			if (aTickCount > aTickLimit)
//			{
//				test->TestTrue(TEXT("The Jet should update it's velocity to match the direction of the forward vector after steering."), !speedNearlyZero && velocityAlignedToPreviousForwardVector);
//				testWorld->bDebugFrameStepExecution = true;
//				return true;
//			}
//			previousForwardVector = jetForwardsVector;
//		}
//	}
//	return false;
//}
//
//
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetUpdatesVelocityDirectionAfterSteeringTest, "ProjectR.Jet Tests.Unit.026: Updates velocity direction after steering", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
//
//bool FAJetUpdatesVelocityDirectionAfterSteeringTest::RunTest(const FString& Parameters)
//{
//
//	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");
//
//	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetAccelerateAndSteerRightCommand);
//	int tickCount = 0;
//	int tickLimit = 3;
//	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetUpdatedVelocityWhenAfterSteeringCommand(tickCount, tickLimit, FVector(0), this));
//
//	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
//
//	return true;
//}







DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetBrakeAndSteerRightCommand);

bool FSpawningAJetBrakeAndSteerRightCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	AJetMOCK* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJetMOCK>();//is a mock necessary??

	testJet->setCurrentXVelocityTo(-10000);//we go reverse and then we try to steer
	testJet->steerRightEveryTick();

	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetInvertSteeringWhenInReverseCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckAJetInvertSteeringWhenInReverseCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		if (testJet)
		{
			bool speedNearlyZero = FMath::IsNearlyZero(testJet->currentSpeed(), 0.1f);
			FVector jetForwardDirection = testJet->GetActorForwardVector();
			bool isMovingBackwards = testJet->goesBackwards();
			float currentZRotation = testJet->GetActorRotation().Yaw;
			bool hasSteeredLeft = currentZRotation < 0;
			bool isMinimalSteering = FMath::IsNearlyZero(currentZRotation, 0.1f);

			UE_LOG(LogTemp, Log, TEXT("Jet rotation vector: %s"), *testJet->GetActorRotation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet %s steered left."), *FString(hasSteeredLeft ? "has" : "hasn't"));
			UE_LOG(LogTemp, Log, TEXT("Jet %s made a minimal steering."), *FString(isMinimalSteering ? "has" : "hasn't"));
			UE_LOG(LogTemp, Log, TEXT("Jet forward vector: %s"), *jetForwardDirection.ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet velocity: %s"), *testJet->GetVelocity().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet velocity projection on forward vector: %s"), *testJet->forwardVelocity().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet velocity projection sign: %s"), *testJet->forwardVelocity().GetSignVector().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet %s moving backwards."), *FString(isMovingBackwards ? "is" : "isn't"));

			if (!speedNearlyZero && !isMinimalSteering && hasSteeredLeft && isMovingBackwards)
			{
				test->TestTrue(TEXT("The Jet should steer right counterclockwise if it's in reverse."), !speedNearlyZero && !isMinimalSteering && hasSteeredLeft && isMovingBackwards);
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


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetInvertsSteeringWhenInReverseTest, "ProjectR.Jet Tests.Unit.027: Inverts steering when in reverse", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetInvertsSteeringWhenInReverseTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetBrakeAndSteerRightCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetInvertSteeringWhenInReverseCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}



DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJeSteerRightWhenIdleCommand);

bool FSpawningAJeSteerRightWhenIdleCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	UWorld* testWorld = sessionUtilities.currentPIEWorld();


	AJetMOCK* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJetMOCK>();

	float direction = 1;//1 is right, -1 is left...
	testJet->SetActorRotation(FRotator(0));//so we are sure to start with zero rotation
	testJet->steer(direction);

	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetUnableToSteerWhenIdleCommand, int, aTickCount, int, aTickLimit, FRotator, previousRotation, FAutomationTestBase*, test);

bool FCheckAJetUnableToSteerWhenIdleCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		if (testJet)
		{

			FRotator currentRotation = testJet->GetActorRotation();
			bool speedNearlyZero = FMath::IsNearlyZero(testJet->currentSpeed(), 0.1f);
			bool hasRotatedFromPreviousRotation = !FMath::IsNearlyEqual(previousRotation.Yaw, currentRotation.Yaw, 0.01f);

			UE_LOG(LogTemp, Log, TEXT("Jet previous rotation: %s"), *previousRotation.ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet current rotation: %s"), *currentRotation.ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet speed: %f"), testJet->currentSpeed());
			UE_LOG(LogTemp, Log, TEXT("Jet speed %s nearly zero."), *FString(speedNearlyZero ? "is" : "isn't"));
			UE_LOG(LogTemp, Log, TEXT("Jet %s rotated from previous rotation."), *FString(hasRotatedFromPreviousRotation ? "has" : "hasn't"));

			++aTickCount;
			if (aTickCount > aTickLimit || hasRotatedFromPreviousRotation)
			{
				test->TestTrue(TEXT("The Jet should update it's velocity to match the direction of the forward vector after steering."), speedNearlyZero && !hasRotatedFromPreviousRotation);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			previousRotation = currentRotation;
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetIsntAbleToSteerWhenIdleTest, "ProjectR.Jet Tests.Unit.028: Isn't able to steer when idle", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetIsntAbleToSteerWhenIdleTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJeSteerRightWhenIdleCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetUnableToSteerWhenIdleCommand(tickCount, tickLimit, FRotator(0), this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetGeneratesOverlapEventsWhenSpawnedTest, "ProjectR.Jet Tests.Unit.029: Generates overlap events when spawned", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetGeneratesOverlapEventsWhenSpawnedTest::RunTest(const FString& Parameters)
{

	AJet* testJet = NewObject<AJet>();

	TestTrue(TEXT("Jet should generate overlap events when spawned into a level."), testJet->bGenerateOverlapEventsDuringLevelStreaming);

	return true;
}



//Necessary so the track generator overlaps with it.
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMeshCollisionIsOfTypePawnTest, "ProjectR.Jet Tests.Unit.030: Jet mesh collision is of type pawn", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetMeshCollisionIsOfTypePawnTest::RunTest(const FString& Parameters)
{
	AJetMOCK* testJet = NewObject<AJetMOCK>();
	{
		TestTrue(TEXT("The jet collision object type should be pawn."), testJet->meshCollisionIsPawn());
	}

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetCommand);

bool FSpawningAJetCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();
	sessionUtilities.spawnInPIEAnInstanceOf<AJetMOCK>();

	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAJetCenterOfMassCommand, FAutomationTestBase*, test);

bool FCheckAJetCenterOfMassCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJetMOCK* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJetMOCK>();
		if (testJet)
		{

			bool centerOfMassLowered = testJet->centerOfMassIsLowered();

			UE_LOG(LogTemp, Log, TEXT("Jet location: %s"), *testJet->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet center of mass: %s"), *testJet->centerOfMass().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet's center of mass %s lowered."), *FString(centerOfMassLowered ? "is" : "isn't"));

			test->TestTrue(TEXT("The Jet should have its center of mass lowered."), centerOfMassLowered);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetHasCenterOfMassLoweredTest, "ProjectR.Jet Tests.Unit.031: Has its center of mass lowered", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetHasCenterOfMassLoweredTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetCommand);

	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetCenterOfMassCommand(this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningTwoJetsMakeOneOfThemItAccelerateAndSteerRightCommand);

bool FSpawningTwoJetsMakeOneOfThemItAccelerateAndSteerRightCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	AJetMOCK* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJetMOCK>();
	FVector aSomewhatDistancedPosition = FVector(10000, 10000, 0);
	sessionUtilities.spawnInPIEAnInstanceOf<AJetMOCK>(aSomewhatDistancedPosition);

	float direction = 1;//1 is right, -1 is left...
	testJet->setCurrentXVelocityTo(30);
	testJet->steerRightEveryTick();



	return true;
}




DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetFallSpeedCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckAJetFallSpeedCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		TArray<AJetMOCK*> testJets = sessionUtilities.retrieveFromPIEAllInstancesOf<AJetMOCK>();

		for (const auto& testJet : testJets)
		{
			if (!testJet)
			{
				return false;
			}
		}

		int index = 0;
		for (const auto& testJet : testJets)
		{
			UE_LOG(LogTemp, Log, TEXT("Jet: %d"), index);
			UE_LOG(LogTemp, Log, TEXT("Jet location: %s"), *testJet->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet rotation: %s"), *testJet->GetActorRotation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet velocity: %s"), *testJet->GetVelocity().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet speed: %f"), testJet->currentSpeed());
			++index;
		}

		float jetAFallSpeed = testJets[0]->getZVelocity();
		float jetBFallSpeed = testJets[1]->getZVelocity();
		bool fallAtSameSpeed = FMath::IsNearlyEqual(jetAFallSpeed, jetBFallSpeed, 0.01f);
		UE_LOG(LogTemp, Log, TEXT("Jets %s fall at same speed."), *FString(fallAtSameSpeed ? "do" : "don't"));

		++aTickCount;
		if (aTickCount > aTickLimit)
		{
			test->TestTrue(TEXT("The Jet should keep falling even if it's steering."), fallAtSameSpeed);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetFallingSpeedWhenSteeringSameAsNoSteeringTest, "ProjectR.Jet Tests.Unit.032: Two jets fall at the same speed even if one moves and steers", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetFallingSpeedWhenSteeringSameAsNoSteeringTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningTwoJetsMakeOneOfThemItAccelerateAndSteerRightCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetFallSpeedCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FSpawningAJetTiltItAndMakeItSteerRightCommand, float, roll);

bool FSpawningAJetTiltItAndMakeItSteerRightCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	AJetMOCK* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJetMOCK>();

	float direction = 1;//1 is right, -1 is left...
	FRotator rollRotator = FRotator(0, 0, roll);
	testJet->SetActorRotation(rollRotator);
	testJet->setCurrentXVelocityTo(10000);//we should set the speed to 1 first so the jet is able to steer.
	testJet->steer(direction);

	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetSteersAroundUpVectorCommand, int, aTickCount, int, aTickLimit, float, roll, FAutomationTestBase*, test);

bool FCheckAJetSteersAroundUpVectorCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJetMOCK* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJetMOCK>();
		if (testJet)
		{
			float currentZRotationAroundUpVector = testJet->GetActorRotation().Pitch;//we rolled, so now it's not the yaw what's changed, it's the pitch.
			bool hasSteeredRight = currentZRotationAroundUpVector < 0;//roll right, then steers right so the pitch is negative.
			bool isMinimalSteering = FMath::IsNearlyZero(currentZRotationAroundUpVector, 0.001f);

			UE_LOG(LogTemp, Log, TEXT("Jet rotation vector: %s"), *testJet->GetActorRotation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet rotation around up vector: %f"), currentZRotationAroundUpVector);
			UE_LOG(LogTemp, Log, TEXT("Jet %s steered right."), *FString(hasSteeredRight ? "has" : "hasn't"));
			UE_LOG(LogTemp, Log, TEXT("Jet %s made a minimal steering."), *FString(isMinimalSteering ? "has" : "hasn't"));

			if (hasSteeredRight && !isMinimalSteering)
			{
				test->TestTrue(TEXT("The Jet pitch rotation should be greater than zero after being tilted and steered."), hasSteeredRight && !isMinimalSteering);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			++aTickCount;

			if (aTickCount > aTickLimit)
			{
				test->TestFalse(TEXT("Tick limit reached for this test. The Jet pitch rotation never changed from zero."), aTickCount > aTickLimit);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetRotatesPitchRightWhenTiltedAndSteersRightTest, "ProjectR.Jet Tests.Unit.033: Rotates pitch right when tilted and steers right", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetRotatesPitchRightWhenTiltedAndSteersRightTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));
	float roll = 30;
	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetTiltItAndMakeItSteerRightCommand(roll));
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSteersAroundUpVectorCommand(tickCount, tickLimit, roll, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAndAccelerateItCommand);

bool FSpawningAJetRotatedOverFloorAndAccelerateItCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	AFloorMeshActor* meshActor = sessionUtilities.spawnInPIEAnInstanceOf<AFloorMeshActor>();

	FVector scale = FVector(4, 4, 1);
	meshActor->SetActorScale3D(scale);

	FVector spawnLocation = meshActor->GetActorLocation() + FVector(0, 0, 1000);

	AJetMOCK* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJetMOCK>(spawnLocation);
	FRotator pitchUp = FRotator(30, 0, 0);
	testJet->SetActorRotation(pitchUp);
	testJet->accelerateOnEveryTick();
	testJet->cancelGravityOnEveryTick();

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetSpeedOrthogonalityToFloorCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckAJetSpeedOrthogonalityToFloorCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJetMOCK* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJetMOCK>();
		AFloorMeshActor* testFloor = sessionUtilities.retrieveFromPIEAnInstanceOf<AFloorMeshActor>();
		if (testJet)
		{
			FVector floorNormal = testFloor->GetActorUpVector();
			FVector jetVelocity = testJet->GetVelocity();
			FVector velocityProjectedOnFloorPlane = FVector::VectorPlaneProject(jetVelocity, floorNormal);
			float speedAlongFloorPlane = velocityProjectedOnFloorPlane.Size();
			float velocityMagnitude = jetVelocity.Size();

			bool isMoving = !FMath::IsNearlyZero(testJet->currentSpeed(), 0.1f);
			bool speedOnFloorIsSameAsJetSpeed = FMath::IsNearlyEqual(speedAlongFloorPlane, testJet->currentSpeed(), 0.001f);
			bool speedOnFloorIsSameAsJetVelocityMagnitude = FMath::IsNearlyEqual(speedAlongFloorPlane, velocityMagnitude, 0.001f);

			UE_LOG(LogTemp, Log, TEXT("Jet location: %s"), *testJet->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet rotation: %s"), *testJet->GetActorRotation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet velocity: %s"), *jetVelocity.ToString());
			UE_LOG(LogTemp, Log, TEXT("Floor up vector: %s"), *floorNormal.ToString());
			UE_LOG(LogTemp, Log, TEXT("Speed along floor plane: %f"), speedAlongFloorPlane);
			UE_LOG(LogTemp, Log, TEXT("Velocity magnitude: %f"), velocityMagnitude);
			UE_LOG(LogTemp, Log, TEXT("Jet speed: %f"), testJet->currentSpeed());
			UE_LOG(LogTemp, Log, TEXT("Jet %s moving."), *FString(isMoving ? "is" : "isn't"));
			UE_LOG(LogTemp, Log, TEXT("Jet %s parallel to floor up vector."), *FString(speedOnFloorIsSameAsJetSpeed ? "moves" : "doesn't move"));

			++aTickCount;

			if (aTickCount > aTickLimit)
			{
				test->TestTrue(TEXT("The Jet should move parallel to the floor. Then, the speed, floor speed and velocity magnitude (gravity is being canceled) should be the same."), isMoving && speedOnFloorIsSameAsJetSpeed && speedOnFloorIsSameAsJetVelocityMagnitude);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}

//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetAcceleratesOrthogonalToSurfaceNormalTest, "ProjectR.Jet Tests.Integration.034: Accelerates orthogonal to the floor surface up vector", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetAcceleratesOrthogonalToSurfaceNormalTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAndAccelerateItCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedOrthogonalityToFloorCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndFloorSideWaysCommand);

bool FSpawningAJetAndFloorSideWaysCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	AFloorMeshActor* testFloor = sessionUtilities.spawnInPIEAnInstanceOf<AFloorMeshActor>();
	FRotator sideways = FRotator(0, 0, 90);
	testFloor->SetActorRotation(sideways);
	FVector floorScale = FVector(5, 5, 1);
	testFloor->SetActorScale3D(floorScale);

	AJet* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJet>();

	float distanceInRangeOfAntiGravityTrigger = testJet->antiGravityHeight() - 200;
	FVector distanceFromFloor = FVector(0, distanceInRangeOfAntiGravityTrigger, 0);
	FVector nearTheFloor = testFloor->GetActorLocation() + distanceFromFloor;
	testJet->SetActorLocation(nearTheFloor);
	testFloor->SetActorRotation(sideways);


	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckAJetSidewaysRejectsFloorCommand, int, aTickCount, int, aTickLimit, float, aPreviousDistance, FAutomationTestBase*, test);

bool FCheckAJetSidewaysRejectsFloorCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		AFloorMeshActor* testFloor = sessionUtilities.retrieveFromPIEAnInstanceOf<AFloorMeshActor>();

		if (testJet && testFloor)
		{
			float currentDistance = testJet->GetActorLocation().Y - testFloor->GetActorLocation().Y;
			bool isRejectingFloor = currentDistance > aPreviousDistance;
			bool sidewaysVelocityNearZero = FMath::IsNearlyZero(testJet->GetVelocity().Y, 0.1f);

			UE_LOG(LogTemp, Log, TEXT("previous distance between floor and jet: %f"), aPreviousDistance);
			UE_LOG(LogTemp, Log, TEXT("current distance between floor and jet: %f"), currentDistance);
			UE_LOG(LogTemp, Log, TEXT("Jet location: %s"), *testJet->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Floor location: %s"), *testFloor->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet velocity: %s"), *testJet->GetVelocity().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet velocity projection on floor up vector: %s"), *testJet->GetVelocity().ProjectOnTo(testFloor->GetActorUpVector()).ToString());
			UE_LOG(LogTemp, Log, TEXT("Floor up vector: %s"), *testFloor->GetActorUpVector().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet up vector: %s"), *testFloor->GetActorUpVector().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet is rejecting floor: %s"), *FString(isRejectingFloor ? "true" : "false"));
			UE_LOG(LogTemp, Log, TEXT("is velocity near zero: %s"), *FString(sidewaysVelocityNearZero ? "true" : "false"));

			if (!sidewaysVelocityNearZero && isRejectingFloor)
			{
				test->TestTrue(TEXT("The jet should reject the nearest floor along the floor up vector."), !sidewaysVelocityNearZero && isRejectingFloor);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}

			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				test->TestFalse(TEXT("Tick limit reached for this test. The jet didn't reject the nearest floor along the floor up vector."), aTickCount > aTickLimit);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			aPreviousDistance = currentDistance;
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSidewaysRejectsAFloorSidewaysTest, "ProjectR.Jet Tests.Integration.035: Activates anti-gravity even if sideways near a sideways floor", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetSidewaysRejectsAFloorSidewaysTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndFloorSideWaysCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSidewaysRejectsFloorCommand(tickCount, tickLimit, std::numeric_limits<float>::max(), this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAndBrakeItCommand);

bool FSpawningAJetRotatedOverFloorAndBrakeItCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	AFloorMeshActor* meshActor = sessionUtilities.spawnInPIEAnInstanceOf<AFloorMeshActor>();

	FVector scale = FVector(4, 4, 1);
	meshActor->SetActorScale3D(scale);

	FVector spawnLocation = meshActor->GetActorLocation() + FVector(0, 0, 1000);

	AJetMOCK* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJetMOCK>(spawnLocation);
	FRotator pitchDown = FRotator(-30, 0, 0);
	testJet->SetActorRotation(pitchDown);
	testJet->brakeOnEveryTick();
	testJet->cancelGravityOnEveryTick();

	return true;
}

//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetBrakesOrthogonalToSurfaceNormalTest, "ProjectR.Jet Tests.Integration.036: Brakes orthogonal to the floor surface up vector", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetBrakesOrthogonalToSurfaceNormalTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAndBrakeItCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedOrthogonalityToFloorCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAccelerateAndSteerItRightCommand);

bool FSpawningAJetRotatedOverFloorAccelerateAndSteerItRightCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}
	PIESessionUtilities sessionUtilities = PIESessionUtilities();

	UWorld* testWorld = sessionUtilities.currentPIEWorld();

	AFloorMeshActor* meshActor = sessionUtilities.spawnInPIEAnInstanceOf<AFloorMeshActor>();

	FVector scale = FVector(4, 4, 1);
	meshActor->SetActorScale3D(scale);

	FVector spawnLocation = meshActor->GetActorLocation() + FVector(0, 0, 1000);

	AJetMOCK* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJetMOCK>(spawnLocation);
	FRotator pitchUp = FRotator(30, 0, 0);
	testJet->SetActorRotation(pitchUp);
	testJet->accelerateOnEveryTick();
	testJet->steerRightEveryTick();
	testJet->cancelGravityOnEveryTick();

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetVelocityMagnitudeOrthogonalityToFloorCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);

bool FCheckAJetVelocityMagnitudeOrthogonalityToFloorCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		AJetMOCK* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJetMOCK>();
		AFloorMeshActor* testFloor = sessionUtilities.retrieveFromPIEAnInstanceOf<AFloorMeshActor>();
		if (testJet)
		{
			FVector floorNormal = testFloor->GetActorUpVector();
			FVector jetVelocity = testJet->GetVelocity();
			FVector velocityProjectedOnFloorPlane = FVector::VectorPlaneProject(jetVelocity, floorNormal);
			float speedAlongFloorPlane = velocityProjectedOnFloorPlane.Size();
			float velocityMagnitude = jetVelocity.Size();

			bool isMoving = !FMath::IsNearlyZero(testJet->currentSpeed(), 0.1f);
			bool speedOnFloorIsSameAsJetVelocityMagnitude = FMath::IsNearlyEqual(speedAlongFloorPlane, velocityMagnitude, 0.001f);

			UE_LOG(LogTemp, Log, TEXT("Jet location: %s"), *testJet->GetActorLocation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet rotation: %s"), *testJet->GetActorRotation().ToString());
			UE_LOG(LogTemp, Log, TEXT("Jet velocity: %s"), *jetVelocity.ToString());
			UE_LOG(LogTemp, Log, TEXT("Floor up vector: %s"), *floorNormal.ToString());
			UE_LOG(LogTemp, Log, TEXT("Speed along floor plane: %f"), speedAlongFloorPlane);
			UE_LOG(LogTemp, Log, TEXT("Velocity magnitude: %f"), velocityMagnitude);
			UE_LOG(LogTemp, Log, TEXT("Jet %s moving."), *FString(isMoving ? "is" : "isn't"));
			UE_LOG(LogTemp, Log, TEXT("Jet %s parallel to floor up vector."), *FString(speedOnFloorIsSameAsJetVelocityMagnitude ? "moves" : "doesn't move"));

			++aTickCount;

			if (aTickCount > aTickLimit)
			{
				test->TestTrue(TEXT("The Jet should move parallel to the floor. Then, the floor speed and velocity magnitude (gravity is being canceled) should be the same."), isMoving && speedOnFloorIsSameAsJetVelocityMagnitude);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}

//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSteersOrthogonalToSurfaceNormalTest, "ProjectR.Jet Tests.Integration.037: steers orthogonal to the floor surface up vector", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetSteersOrthogonalToSurfaceNormalTest::RunTest(const FString& Parameters)
{

	FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");

	ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName));

	ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

	ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetRotatedOverFloorAccelerateAndSteerItRightCommand);
	int tickCount = 0;
	int tickLimit = 3;
	ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetVelocityMagnitudeOrthogonalityToFloorCommand(tickCount, tickLimit, this));

	ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);

	return true;
}

//jet mesh should be set to collision enabled. (query and physics or physics only).
//delete tests that check velocity alignment to forward or backwards vectors after steering. Or see if it's possible to remade them.
//create a state with state factory to handle the direction that the jet is heading (forwards or backwards). It should update itself every time that acceleration or brake is called.
// maybe move that inReverseInverts method in the steer component to it.


#endif //WITH_DEV_AUTOMATION_TESTS