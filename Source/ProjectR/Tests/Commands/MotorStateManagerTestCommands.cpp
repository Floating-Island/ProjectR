// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "MotorStateManagerTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "../Mocks/MotorStateManagerMOCK.h"
#include "Jet/MotorStates/NeutralMotorState.h"


//Test preparation commands:

bool FSpawnAMotorStateManager::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		sessionUtilities.spawnInPIEAnInstanceOf<AMotorStateManagerMOCK>();
		
		return true;
	}

	return false;
}


//Test check commands:


bool FCheckMotorStateManagerDefaultState::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
		if(testManager)
		{
			test->TestTrue(TEXT("The default state should be NeutralMotorState"), testManager->currentState()->GetClass() == ANeutralMotorState::StaticClass() );
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;	
		}
	}
	return false;
}


#endif //WITH_DEV_AUTOMATION_TESTS
