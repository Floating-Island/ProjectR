// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "MotorStateManagerTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "../Mocks/MotorStateManagerMOCK.h"
#include "Jet/MotorStates/NeutralMotorState.h"
#include "Jet/MotorStates/AcceleratingMotorState.h"
#include "Jet/MotorStates/ReversingMotorState.h"


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


bool FSpawnAMotorStateManagerAndAccelerateIt::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.spawnInPIEAnInstanceOf<AMotorStateManagerMOCK>();

		testManager->accelerate();
		
		return true;
	}

	return false;
}


bool FSpawnAMotorStateManagerAndBrakeIt::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.spawnInPIEAnInstanceOf<AMotorStateManagerMOCK>();

		testManager->brake();
		
		return true;
	}

	return false;
}


bool FSpawnAMotorStateManagerAndNeutralizeIt::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.spawnInPIEAnInstanceOf<AMotorStateManagerMOCK>();

		testManager->brake();//first change it to another state.
		testManager->neutralize();
		
		return true;
	}

	return false;
}


bool FSpawnAMotorStateManagerBrakeAccelerateAndNeutralizeIt::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.spawnInPIEAnInstanceOf<AMotorStateManagerMOCK>();

		testManager->brake();
		testManager->accelerate();
		testManager->neutralize();
		
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


bool FCheckMotorStateManagerStateChangesToAccelerating::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
		if(testManager)
		{
			test->TestTrue(TEXT("After accelerate, the motorState should be Accelerating"), testManager->currentState()->GetClass() == AAcceleratingMotorState::StaticClass() );
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;	
		}
	}
	return false;
}


bool FCheckMotorStateManagerStateChangesToReversing::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
		if(testManager)
		{
			test->TestTrue(TEXT("After brake, the motorState should be Reversing"), testManager->currentState()->GetClass() == AReversingMotorState::StaticClass() );
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;	
		}
	}
	return false;
}


bool FCheckMotorStateManagerStateChangesToNeutral::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
		if(testManager)
		{
			test->TestTrue(TEXT("After neutralize, the motorState should be Neutral"), testManager->currentState()->GetClass() == ANeutralMotorState::StaticClass() );
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;	
		}
	}
	return false;
}


bool FCheckMotorStateManagerAccelerateKeepsStateIfAccelerating::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
		if(testManager)
		{
			testManager->accelerate();
			AMotorState* currentState = testManager->currentState();
			bool statesMatch = previousState == currentState;
			
			if(statesMatch)
			{
				test->TestTrue(TEXT("Should keep its state if accelerate when already Accelerating"), statesMatch );
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;	
			}
			previousState = currentState;

			++tickCount;
			if(tickCount > tickLimit)
			{
				test->TestTrue(TEXT("Should keep its state if accelerate when already Accelerating"), statesMatch );
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckMotorStateManagerBrakeKeepsStateIfReversing::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
		if(testManager)
		{
			testManager->brake();
			AMotorState* currentState = testManager->currentState();
			bool statesMatch = previousState == currentState;
			
			if(statesMatch)
			{
				test->TestTrue(TEXT("Should keep its state if brake when already Reversing"), statesMatch );
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;	
			}
			previousState = currentState;
			
			++tickCount;
			if(tickCount > tickLimit)
			{
				test->TestTrue(TEXT("Should keep its state if brake when already Reversing"), statesMatch );
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckMotorStateManagerNeutralizeKeepsStateIfNeutral::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
		if(testManager)
		{
			testManager->neutralize();
			AMotorState* currentState = testManager->currentState();
			bool statesMatch = previousState == currentState;
			
			if(statesMatch)
			{
				test->TestTrue(TEXT("Should keep its state if neutralize when already Neutral"), statesMatch );
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;	
			}
			previousState = currentState;
			
			++tickCount;
			if(tickCount > tickLimit)
			{
				test->TestTrue(TEXT("Should keep its state if neutralize when already Neutral"), statesMatch );
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckMotorStateManagerLeavesOneStateInWorld::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AMotorStateManagerMOCK* testManager = sessionUtilities.retrieveFromPIEAnInstanceOf<AMotorStateManagerMOCK>();
		if(testManager)
		{
			int statesInWorld = sessionUtilities.retrieveFromPIEAllInstancesOf<AMotorState>().Num();	
			test->TestTrue(TEXT("After accelerating, braking and/or neutralizing, only one motor state remains in the world"), statesInWorld == 1 );
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;	
		}
	}
	return false;	
}





#endif //WITH_DEV_AUTOMATION_TESTS
