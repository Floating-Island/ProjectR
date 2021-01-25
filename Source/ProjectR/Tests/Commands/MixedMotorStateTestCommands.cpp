// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "MixedMotorStateTestCommands.h"
#include "Jet/MotorStates/MixedMotorState.h"
#include "../Utilities/PIESessionUtilities.h"
#include "../Mocks/JetMOCK.h"


//Test preparation commands:


bool FSpawningAJetAndActivateMixedMotorState::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		UWorld* testWorld = sessionUtilities.defaultPIEWorld();

		AJetMOCK* testJet = sessionUtilities.spawnInPIEAnInstanceOf<AJetMOCK>();

		UMixedMotorState* testState = NewObject<UMixedMotorState>();

		testState->activate(testJet->motorDriveComponent());

		return true;
	}
	return false;
}











//Test check commands:


bool FCheckMixedStateActivation::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.defaultPIEWorld();
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		AFloorMeshActor* testFloor = sessionUtilities.retrieveFromPIEAnInstanceOf<AFloorMeshActor>();

		if (testJet && testFloor)
		{
			float currentSpeed = testJet->currentSpeed();
			bool sumIsBiggerThanZero = testJet->acceleration() - testJet->brakeValue() > 0;
			bool speedHasBeenUpdated = (sumIsBiggerThanZero ? currentSpeed > previousSpeed : currentSpeed < previousSpeed) && !FMath::IsNearlyEqual(currentSpeed, previousSpeed, 0.1f);
			speedHasBeenUpdated = (FMath::IsNearlyEqual(testJet->acceleration(), testJet->brakeValue())) ? true : speedHasBeenUpdated;// if they're the same value, assume that the speed has been updated.

			UE_LOG(LogTemp, Log, TEXT("previous distance between floor and jet: %f"), previousSpeed);
			UE_LOG(LogTemp, Log, TEXT("current distance between floor and jet: %f"), currentSpeed);
			UE_LOG(LogTemp, Log, TEXT("Jet acceleration value: %f"), testJet->acceleration());
			UE_LOG(LogTemp, Log, TEXT("Jet brake value: %f"), testJet->brakeValue());
			UE_LOG(LogTemp, Log, TEXT("acceleration and brake sum %s bigger than zero."), *FString(sumIsBiggerThanZero ? "is" : "isn't"));
			UE_LOG(LogTemp, Log, TEXT("Jet speed %s been updated."), *FString(speedHasBeenUpdated ? "has" : "hasn't"));

			if (speedHasBeenUpdated)
			{
				test->TestTrue(TEXT("Activating the mixed state should accelerate and brake the jet."), speedHasBeenUpdated);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}

			++tickCount;
			if (tickCount > tickLimit)
			{
				test->TestFalse(TEXT("Tick limit reached for this test. Activating the mixed state didn't accelerate and brake the jet."), tickCount > tickLimit);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}
			previousSpeed = currentSpeed;
		}
	}
	return false;
}





#endif //WITH_DEV_AUTOMATION_TESTS
