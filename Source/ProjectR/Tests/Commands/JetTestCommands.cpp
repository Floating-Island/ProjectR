// Fill out your copyright notice in the Description page of Project Settings.






#if WITH_DEV_AUTOMATION_TESTS

#include "JetTestCommands.h"
#include "Jet/Jet.h"
#include "../Mocks/JetMOCK.h"

#include "Editor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"

#include "../Utilities/PIESessionUtilities.h"
#include "../Utilities/FloorMeshActor.h"

//Test preparation commands:

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







//Test check commands:







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



#endif //WITH_DEV_AUTOMATION_TESTS