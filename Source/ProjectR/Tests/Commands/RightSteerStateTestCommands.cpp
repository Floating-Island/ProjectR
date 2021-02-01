// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "RightSteerStateTestCommands.h"
#include "../../Public/Jet/SteerStates/RightSteerState.h"
#include "../Utilities/PIESessionUtilities.h"
#include "../Mocks/JetMOCK.h"

//Test preparation commands:

bool FSpawningRightSteerStateAndActivateIt::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		URightSteerState* testState = NewObject<URightSteerState>();
		return true;
	}
	return false;
}



//Test check commands:


bool FCheckAJetSteersRight::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		FWorldContext serverContext = GEditor->GetWorldContexts()[1];
		AJetMOCK* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJetMOCK>();
		if(testJet)
		{
			TArray<UObject*> objectsFound = TArray<UObject*>();
			GetObjectsOfClass(URightSteerState::StaticClass(),objectsFound);
			URightSteerState* steerState = Cast<URightSteerState, UObject>(objectsFound[0]);
			if(steerState)
			{
				steerState->activate(testJet->steeringComponent());
			}
			else
			{
				return false;
			}
			UE_LOG(LogTemp, Log, TEXT("Previous jet location: %s"), *previousLocation.ToString());
			FVector currentLocation = testJet->GetActorLocation();
			UE_LOG(LogTemp, Log, TEXT("Current jet location: %s"), *currentLocation.ToString());
			float currentYLocation = currentLocation.Y;
			bool hasSteeredTowardsY = !FMath::IsNearlyEqual(previousLocation.Y, currentYLocation, 0.001f) && currentYLocation > previousLocation.Y;

			if(hasSteeredTowardsY)
			{
				test->TestTrue(TEXT("The right steer state should steer right the steering component passed as parameter."), hasSteeredTowardsY);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
			previousLocation = currentLocation;

			++tickCount;
			if(tickCount > tickLimit)
			{
				test->TestTrue(TEXT("The right steer state should steer right the steering component passed as parameter."), hasSteeredTowardsY);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
