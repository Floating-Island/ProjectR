// Fill out your copyright notice in the Description page of Project Settings.


#include "JetTest.h"

#include "Jet.h"
#include "Mocks/JetMOCK.h"

#include "Misc/AutomationTest.h"
//to be able to simulate:
#include "Tests/AutomationEditorCommon.h"
#include "Editor.h"
#include "Kismet/GameplayStatics.h"
//to be able to process inputs:
#include "GameFramework/PlayerInput.h"
#include "GameFramework/GameModeBase.h"


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



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldHaveAStaticMeshTest, "ProjectR.Unit.JetTests.ShouldHaveAStaticMesh", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldHaveAStaticMeshTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();
		
		TestTrue(TEXT("The Jet static mesh shouldn't be null if it has one."), testJet->hasAStaticMesh());
	}

	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetMeshShouldBeTheRootComponentTest, "ProjectR.Unit.JetTests.MeshShouldBeTheRootComponent", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetMeshShouldBeTheRootComponentTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();
		
		TestTrue(TEXT("The Jet static mesh should be the root component."), testJet->isMeshTheRootComponent());
	}

	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldHaveGravityEnabledTest, "ProjectR.Unit.JetTests.ShouldHaveGravityEnabled", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldHaveGravityEnabledTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();
		
		TestTrue(TEXT("The Jet should have gravity enabled."), testJet->hasGravityEnabled());
	}

	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldntAffectNavigationVolumeTest, "ProjectR.Unit.JetTests.ShouldntAffectNavigationVolume", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldntAffectNavigationVolumeTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();
		
		TestFalse(TEXT("The Jet shouldn't affect the navigation volume."), testJet->isAffectingNavigation());
	}

	return true;
}



//uses a MOCK
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldBeMovableTest, "ProjectR.Unit.JetTests.ShouldBeMovable", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldBeMovableTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();
		
		TestTrue(TEXT("The Jet should be movable when spawned into the world."), testJet->IsRootComponentMovable());
	}

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

	UWorld* testWorld = GEditor->GetPIEWorldContext()->World();

	AJet* testJet = testWorld->SpawnActor<AJet>(AJet::StaticClass());

	testJet->accelerate();

	return true;
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetLocationCommand, int*, tickCount, int, tickLimit, FAutomationTestBase*, test);

bool FCheckAJetLocationCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		UWorld* testWorld = GEditor->GetPIEWorldContext()->World();
		AJet* testJet = Cast<AJet, AActor>(UGameplayStatics::GetActorOfClass(testWorld, AJet::StaticClass()));
		if (testJet)
		{
			float currentXLocation = testJet->GetActorLocation().X;


			if (currentXLocation > 0 && !FMath::IsNearlyZero(currentXLocation, 0.1f))//it would be better to align the ship first and then check against it's forward vector. We have to be careful of gravity in this test.
			{
				test->TestTrue(TEXT("The Jet X location should increase after an acceleration is added (after ticking)."), currentXLocation > 0 && !FMath::IsNearlyZero(currentXLocation, 0.1f));
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			*tickCount = *tickCount + 1;

			if ( (*tickCount) > tickLimit)
			{
				test->TestFalse(TEXT("Tick limit reached for this test. The Jet X Location never changed from zero."), *tickCount > tickLimit);
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
	{
		FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");
		
		ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName))

		ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

		ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItAccelerateCommand);
		int* tickCount = new int{0};
		int tickLimit = 3;
		ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetLocationCommand(tickCount, tickLimit, this));

		ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	}

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetSpeedIncreaseCommand, int*, tickCount, int, tickLimit, FAutomationTestBase*, test);

bool FCheckAJetSpeedIncreaseCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		UWorld* testWorld = GEditor->GetPIEWorldContext()->World();
		AJet* testJet = Cast<AJet, AActor>(UGameplayStatics::GetActorOfClass(testWorld, AJet::StaticClass()));
		if (testJet)
		{
			float currentSpeed = testJet->currentSpeed();


			if (currentSpeed > 0 && !FMath::IsNearlyZero(currentSpeed, 0.1f))//it would be better to align the ship first and then check against it's forward vector. We have to be careful of gravity in this test.
			{
				test->TestTrue(TEXT("The Jet speed should increase after accelerating (after ticking)."), currentSpeed > 0 && !FMath::IsNearlyZero(currentSpeed, 0.1f));
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}

			*tickCount = *tickCount + 1;

			if ( (*tickCount) > tickLimit)
			{
				test->TestFalse(TEXT("Tick limit reached for this test. The Jet speed never changed from zero."), *tickCount > tickLimit);
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
	{
		FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");
		
		ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName))

		ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

		ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItAccelerateCommand);
		int* tickCount = new int{0};
		int tickLimit = 3;
		ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedIncreaseCommand(tickCount, tickLimit, this));

		ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	}

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
	if (!GEditor->IsPlayingSessionInEditor())//if not, everything would be made while the map is loading and the PIE is in progress.
	{
		return false;
	}

	UWorld* testWorld = GEditor->GetPIEWorldContext()->World();

	AJet* testJet = testWorld->SpawnActor<AJet>(AJet::StaticClass());

	testJet->brake();

	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetSpeedDecreaseCommand, int*, tickCount, int, tickLimit, FAutomationTestBase*, test);

bool FCheckAJetSpeedDecreaseCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		UWorld* testWorld = GEditor->GetPIEWorldContext()->World();
		AJet* testJet = Cast<AJet, AActor>(UGameplayStatics::GetActorOfClass(testWorld, AJet::StaticClass()));
		if (testJet)
		{
			float currentSpeed = testJet->currentSpeed();


			if (currentSpeed < 0 && !FMath::IsNearlyZero(currentSpeed, 0.1f))//it would be better to align the ship first and then check against it's forward vector. We have to be careful of gravity in this test.
			{
				test->TestTrue(TEXT("The Jet speed should decrease after a brake (after ticking)."), currentSpeed < 0 && !FMath::IsNearlyZero(currentSpeed, 0.1f));
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			*tickCount = *tickCount + 1;

			if ( (*tickCount) > tickLimit)
			{
				test->TestFalse(TEXT("Tick limit reached for this test. The Jet speed never changed from zero."), *tickCount > tickLimit);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpeedDecreasesWhenBrakesTest, "ProjectR.Unit.JetTests.SpeedDecreasesWhenBrakes", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetSpeedDecreasesWhenBrakesTest::RunTest(const FString& Parameters)
{
	{
		FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");
		
		ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName))

		ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

		ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItBrakeCommand);
		int* tickCount = new int{0};
		int tickLimit = 3;
		ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedDecreaseCommand(tickCount, tickLimit, this));

		ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	}

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

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetSpeedAgainstTopSpeedCommand, int*, tickCount, int, tickLimit, FAutomationTestBase*, test);

bool FCheckAJetSpeedAgainstTopSpeedCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		UWorld* testWorld = GEditor->GetPIEWorldContext()->World();
		AJetMOCK* testJet = Cast<AJetMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, AJetMOCK::StaticClass()));
		if (testJet)
		{
			float currentSpeed = testJet->currentSpeed();

			*tickCount = *tickCount + 1;
			

			if ( (*tickCount) > tickLimit)
			{
				test->TestTrue(TEXT("If a jet is at top speed, it should never increase it after an acceleration is added (after ticking)."), FMath::IsNearlyEqual(currentSpeed, testJet->settedTopSpeed(), 1.0f));
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
	{
		FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");
		
		ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName))

		ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

		ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetSetVelocityToTopSpeedCommand);
		int* tickCount = new int{0};
		int tickLimit = 3;
		ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedAgainstTopSpeedCommand(tickCount, tickLimit, this));

		ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	}

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItSteerRightCommand);

bool FSpawningAJetMakeItSteerRightCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())//if not, everything would be made while the map is loading and the PIE is in progress.
	{
		return false;
	}

	UWorld* testWorld = GEditor->GetPIEWorldContext()->World();

	AJet* testJet = testWorld->SpawnActor<AJet>(AJet::StaticClass());

	float direction = 1;//1 is right, -1 is left...
	
	testJet->steer(direction);

	return true;
}


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckAJetMovedRightCommand, int*, tickCount, int, tickLimit, FAutomationTestBase*, test);

bool FCheckAJetMovedRightCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		UWorld* testWorld = GEditor->GetPIEWorldContext()->World();
		AJet* testJet = Cast<AJet, AActor>(UGameplayStatics::GetActorOfClass(testWorld, AJet::StaticClass()));
		if (testJet)
		{
			float currentYLocation = testJet->GetActorLocation().Y;


			if (currentYLocation > 0  && !FMath::IsNearlyZero(currentYLocation, 0.1f))//we should be careful of near zero floats. Maybe !NearEqual would be better...
			{
				test->TestTrue(TEXT("The Jet Y location should be greater than zero after steering right (after ticking)."), currentYLocation > 0 && !FMath::IsNearlyZero(currentYLocation, 0.1f));
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			*tickCount = *tickCount + 1;

			if ( (*tickCount) > tickLimit)
			{
				test->TestFalse(TEXT("Tick limit reached for this test. The Jet Y location never changed from zero."), *tickCount > tickLimit);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldMoveRightWhenSteeringRightTest, "ProjectR.Unit.JetTests.ShouldMoveRightWhenSteeringRight", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldMoveRightWhenSteeringRightTest::RunTest(const FString& Parameters)
{
	{
		FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");
		
		ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName))

		ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

		ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetMakeItSteerRightCommand);
		int* tickCount = new int{0};
		int tickLimit = 3;
		ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetMovedRightCommand(tickCount, tickLimit, this));

		ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	}

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
	if (!GEditor->IsPlayingSessionInEditor())//if not, everything would be made while the map is loading and the PIE is in progress.
	{
		return false;
	}

	UWorld* testWorld = GEditor->GetPIEWorldContext()->World();

	AJet* testJet = testWorld->SpawnActor<AJet>(AJet::StaticClass());
	AGameModeBase* testGameMode = testWorld->GetAuthGameMode();

	testGameMode->SpawnPlayerFromSimulate(FVector(), FRotator());

	
	APlayerController* jetController = Cast<APlayerController,AActor>(testGameMode->GetGameInstance()->GetFirstLocalPlayerController(testWorld));

	FName const accelerateActionName = FName(TEXT("AccelerateAction"));
	TArray<FInputAxisKeyMapping> axisMappings = jetController->PlayerInput->GetKeysForAxis(accelerateActionName);//in the editor, we are going to add a new axis mapping inside Project settings -> Input
	//in the jet class, we are going to add a player input binding with:
	//	PlayerInputComponent->BindAxis("AccelerateAction",this, &AJet::accelerate);
	//and in the constructor:
	//AutoPossessPlayer = EAutoReceiveInput::Player0;//this should be changed when we start doing multiplayer. It won't work.
	FKey accelerateKey;
	for(auto axisMap: axisMappings)
	{
		if(axisMap.Scale > 0)
		{
			accelerateKey = axisMap.Key;
			break;
		}
	}
	
	jetController->InputKey(accelerateKey,EInputEvent::IE_Repeat,5.0f,false);

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetAcceleratesWhenPressingAccelerationKeyTest, "ProjectR.Unit.JetTests.AcceleratesWhenPressingAccelerationKey", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetAcceleratesWhenPressingAccelerationKeyTest::RunTest(const FString& Parameters)
{
	{
		FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");
		
		ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName))

		ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

		ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressAccelerationKeyCommand);
		int* tickCount = new int{0};
		int tickLimit = 3;
		ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedIncreaseCommand(tickCount, tickLimit, this));

		ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	}

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressSteerRightKeyCommand);

bool FSpawningAJetPressSteerRightKeyCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())//if not, everything would be made while the map is loading and the PIE is in progress.
	{
		return false;
	}

	UWorld* testWorld = GEditor->GetPIEWorldContext()->World();

	AJet* testJet = testWorld->SpawnActor<AJet>(AJet::StaticClass());
	AGameModeBase* testGameMode = testWorld->GetAuthGameMode();

	testGameMode->SpawnPlayerFromSimulate(FVector(), FRotator());

	
	APlayerController* jetController = Cast<APlayerController,AActor>(testGameMode->GetGameInstance()->GetFirstLocalPlayerController(testWorld));

	FName const steerRightActionName = FName(TEXT("SteerAction"));
	
	TArray<FInputAxisKeyMapping> axisMappings = jetController->PlayerInput->GetKeysForAxis(steerRightActionName);
	FKey SteerRightKey;
	for(auto axisMap: axisMappings)
	{
		if(axisMap.Scale > 0)
		{
			SteerRightKey = axisMap.Key;
			break;
		}
	}
	jetController->InputKey(SteerRightKey,EInputEvent::IE_Repeat,5.0f,false);

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldMoveRightWhenPressingSteerRightKeyTest, "ProjectR.Unit.JetTests.ShouldMoveRightWhenPressingSteerRightKey", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldMoveRightWhenPressingSteerRightKeyTest::RunTest(const FString& Parameters)
{
	{
		FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");
		
		ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName))

		ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

		ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressSteerRightKeyCommand);
		int* tickCount = new int{0};
		int tickLimit = 3;
		ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetMovedRightCommand(tickCount, tickLimit, this));

		ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	}

	return true;
}






DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressBrakeKeyCommand);

bool FSpawningAJetPressBrakeKeyCommand::Update()
{
	if (!GEditor->IsPlayingSessionInEditor())
	{
		return false;
	}

	UWorld* testWorld = GEditor->GetPIEWorldContext()->World();

	AJet* testJet = testWorld->SpawnActor<AJet>(AJet::StaticClass());
	AGameModeBase* testGameMode = testWorld->GetAuthGameMode();

	testGameMode->SpawnPlayerFromSimulate(FVector(), FRotator());

	
	APlayerController* jetController = Cast<APlayerController,AActor>(testGameMode->GetGameInstance()->GetFirstLocalPlayerController(testWorld));

	FName const brakeActionName = FName(TEXT("BrakeAction"));
	FKey brakeKey = TArray<FInputActionKeyMapping>(jetController->PlayerInput->GetKeysForAction(brakeActionName))[0].Key;
    
	jetController->InputKey(brakeKey,EInputEvent::IE_Repeat,5.0f,false);

	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetBrakesWhenPressingBrakeKeyTest, "ProjectR.Unit.JetTests.BrakesWhenPressingBrakeKey", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetBrakesWhenPressingBrakeKeyTest::RunTest(const FString& Parameters)
{
	{
		FString testWorldName = FString("/Game/Tests/TestMaps/VoidWorld");
		
		ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(testWorldName))

		ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(true));

		ADD_LATENT_AUTOMATION_COMMAND(FSpawningAJetPressBrakeKeyCommand);
		int* tickCount = new int{0};
		int tickLimit = 3;
		ADD_LATENT_AUTOMATION_COMMAND(FCheckAJetSpeedDecreaseCommand(tickCount, tickLimit, this));

		ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand);
	}

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




IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldHaveACameraTest, "ProjectR.Unit.JetTests.ShouldHaveACamera", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldHaveACameraTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();
		
		TestTrue(TEXT("The Jet should have a camera."), testJet->HasCameraComponent());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetShouldHaveACameraAttachedToSpringArmTest, "ProjectR.Unit.JetTests.ShouldHaveACameraAttachedToSpringArm", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetShouldHaveACameraAttachedToSpringArmTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();
		
		TestTrue(TEXT("The Jet should have a camera."), testJet->isCameraAttachedToSpringArm());
	}

	return true;
}



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAJetSpringArmShouldUseAbsoluteRotationTest, "ProjectR.Unit.JetTests.SpringArmShouldUseAbsoluteRotation", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FAJetSpringArmShouldUseAbsoluteRotationTest::RunTest(const FString& Parameters)
{
	{
		AJetMOCK* testJet = NewObject<AJetMOCK>();
		
		TestTrue(TEXT("The Jet should have a camera."), testJet->usesAbsoluteRotation());
	}

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS