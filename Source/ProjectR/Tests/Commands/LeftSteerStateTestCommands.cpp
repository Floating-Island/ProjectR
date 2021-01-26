// Fill out your copyright notice in the Description page of Project Settings.


#include "../Mocks/JetMOCK.h"
#if WITH_DEV_AUTOMATION_TESTS

#include "LeftSteerStateTestCommands.h"
#include "Jet/Jet.h"
#include "../Utilities/PIESessionUtilities.h"
#include "Jet/SteerStates/LeftSteerState.h"

//Test preparation commands:


bool FSpawningLeftSteerStateAndActivateIt::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		AJetMOCK* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJetMOCK>();
		if(testJet)
		{
			ULeftSteerState* testState = sessionUtilities.spawnInPIEAnInstanceOf<ULeftSteerState>();
			testState->activate(testJet->steeringComponent());
			return true;
		}
	}
	return false;
}









//Test check commands:



bool FCheckAJetSteersLeft::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		FWorldContext serverContext = GEditor->GetWorldContexts()[1];
		AJet* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJet>();
		if(testJet)
		{
			UE_LOG(LogTemp, Log, TEXT("Previous jet location: %s"), *previousLocation.ToString());
			FVector currentLocation = testJet->GetActorLocation();
			UE_LOG(LogTemp, Log, TEXT("Current jet location: %s"), *currentLocation.ToString());
			float currentYLocation = currentLocation.Y;
			bool hasSteeredTowardsY = !FMath::IsNearlyEqual(previousLocation.Y, currentYLocation, 0.01f) && currentYLocation < previousLocation.Y;

			if(hasSteeredTowardsY)
			{
				test->TestTrue(TEXT("The left steer state should steer left the steering component passed as parameter."), hasSteeredTowardsY);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
			previousLocation = currentLocation;

			++tickCount;
			if(tickCount > tickLimit)
			{
				test->TestTrue(TEXT("The left steer state should steer left the steering component passed as parameter."), hasSteeredTowardsY);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


#endif //WITH_DEV_AUTOMATION_TESTS
