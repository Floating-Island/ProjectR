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




//Test check commands:


bool FCheckSteerStateManagerCurrentState::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		ASteerStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<ASteerStateManagerMOCK>();
		if(testManager)
		{
			test->TestTrue((TEXT("%s"), *message), testManager->currentState()->GetClass() == expectedState );
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;	
		}
	}
	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
