// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "SteerStateManagerTestCommands.h"
#include "Jet/SteerStates/CenterSteerState.h"

#include "../Mocks/SteerStateManagerMOCK.h"
#include "../Utilities/PIESessionUtilities.h"

//Test preparation commands:

bool FSpawnASteerStateManagerMOCK::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		sessionUtilities.spawnInPIEAnInstanceOf<ASteerStateManagerMOCK>();
		
		return true;
	}
	return false;
}


bool FLeftSteerASteerStateManagerMOCK::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		ASteerStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ASteerStateManagerMOCK>();

		if(testManager)
		{
			testManager->steerLeft();
			return true;
		}
	}
	return false;
}


bool FRightSteerASteerStateManagerMOCK::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		ASteerStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ASteerStateManagerMOCK>();

		if(testManager)
		{
			testManager->steerRight();
			return true;
		}
	}
	return false;
}







//Test check commands:


bool FCheckSteerStateManagerCurrentState::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		ASteerStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ASteerStateManagerMOCK>();
		if(testManager)
		{
			UE_LOG(LogTemp, Log, TEXT("current state: %s"), *testManager->currentState()->GetName());
			bool statesMatch = testManager->currentState()->GetClass() == expectedState;
			if(statesMatch)
			{
				test->TestTrue((TEXT("%s"), *message), statesMatch );
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}

			++tickCount;
			if(tickCount>tickLimit)
			{
				test->TestTrue((TEXT("Tick limit reached. %s"), *message), statesMatch );
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
