// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "RightSteerStateTestCommands.h"
#include "../../Public/Jet/SteerStates/RightSteerState.h"
#include "../Utilities/PIESessionUtilities.h"
#include "../Mocks/JetMOCK.h"
#include "../Utilities/ObjectContainerActor.h"

//Test preparation commands:



//Test check commands:


bool FCheckAJetSteersRight::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		FWorldContext serverContext = GEditor->GetWorldContexts()[1];
		AJetMOCK* testJet = sessionUtilities.retrieveFromPIEAnInstanceOf<AJetMOCK>();
		AObjectContainerActor* testContainer = sessionUtilities.retrieveFromPIEAnInstanceOf<AObjectContainerActor>();
		if(testJet && testContainer)
		{
			URightSteerState* steerState = Cast<URightSteerState, UObject>(testContainer->retrieveStoredObject());
			if(steerState==nullptr)
			{
				testContainer->storeObjectOfType<URightSteerState>();
				steerState = Cast<URightSteerState, UObject>(testContainer->retrieveStoredObject());
			}

			steerState->activate(testJet->steeringComponent());
			
			UE_LOG(LogTemp, Log, TEXT("Previous jet location: %s"), *previousLocation.ToString());
			FVector currentLocation = testJet->GetActorLocation();
			UE_LOG(LogTemp, Log, TEXT("Current jet location: %s"), *currentLocation.ToString());
			float currentYLocation = currentLocation.Y;
			bool hasSteeredTowardsY = !FMath::IsNearlyEqual(previousLocation.Y, currentYLocation, 0.001f) && currentYLocation > previousLocation.Y;

			if(hasSteeredTowardsY)
			{
				test->TestTrue(test->conditionMessage(), hasSteeredTowardsY);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
			previousLocation = currentLocation;

			return test->manageTickCountTowardsLimit();
		}
	}
	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
