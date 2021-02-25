// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "RacePlayerStateTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "../TestBaseClasses/SimplePIETestBase.h"
#include "PlayerState/RacePlayerState.h"
#include "UI/RacePlayerUI.h"

//Test preparation commands:



//Test check commands:


bool FCheckPlayerStateUpdatesRacePlayerUICurrentLap::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
	
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		URacePlayerUI* testRaceUI = sessionUtilities.retrieveFromPIEAnInstanceOf<URacePlayerUI>();
		if (testRaceUI)
		{
			
			ARacePlayerState* testState = sessionUtilities.retrieveFromPIEAnInstanceOf<ARacePlayerState>();
			if(testState == nullptr)
			{
				sessionUtilities.spawnInPIEAnInstanceOf<ARacePlayerState>();
				return false;
			}

			testState->subscribeToLapUpdate(testRaceUI);

			int arbitraryLapNumber = 5;
			testState->updateLapTo(arbitraryLapNumber);

			int stateCurrentLap = testState->currentLap();
			UE_LOG(LogTemp, Log, TEXT("current player state lap: %d."), stateCurrentLap);
			
			int uiCurrentLap = testRaceUI->currentLap();
			UE_LOG(LogTemp, Log, TEXT("current race player ui lap: %d."), uiCurrentLap);

			bool lapsMatch = stateCurrentLap == uiCurrentLap;

			if(lapsMatch)
			{
				test->TestTrue(test->conditionMessage(), lapsMatch);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
			return test->manageTickCountTowardsLimit();
		}
	}
	return false;
}





#endif //WITH_DEV_AUTOMATION_TESTS
