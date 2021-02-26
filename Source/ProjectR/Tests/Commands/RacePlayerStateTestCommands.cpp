// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "RacePlayerStateTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "../TestBaseClasses/SimplePIETestBase.h"
#include "../Utilities/BlueprintWidgetContainerPawn.h"
#include "PlayerState/RacePlayerState.h"
#include "UI/RacePlayerUI.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

//Test preparation commands:



//Test check commands:


bool FCheckPlayerStateUpdatesRacePlayerUICurrentLap::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
	
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		
		ABlueprintWidgetContainerPawn* testContainer = sessionUtilities.retrieveFromPIEAnInstanceOf<ABlueprintWidgetContainerPawn>();
		if(testContainer == nullptr)
		{
			return false;
		}
		
		URacePlayerUI* testRaceUI = Cast<URacePlayerUI, UUserWidget>(testContainer->retrieveWidget());
		if (testRaceUI == nullptr)
		{
			return false;
		}
		
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
	return false;
}


bool FCheckPlayerStateUpdatesRacePlayerUICurrentPosition::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
	
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		
		ABlueprintWidgetContainerPawn* testContainer = sessionUtilities.retrieveFromPIEAnInstanceOf<ABlueprintWidgetContainerPawn>();
		if(testContainer == nullptr)
		{
			return false;
		}
		
		URacePlayerUI* testRaceUI = Cast<URacePlayerUI, UUserWidget>(testContainer->retrieveWidget());
		if (testRaceUI == nullptr)
		{
			return false;
		}
		
		ARacePlayerState* testState = sessionUtilities.retrieveFromPIEAnInstanceOf<ARacePlayerState>();
		if(testState == nullptr)
		{
			sessionUtilities.spawnInPIEAnInstanceOf<ARacePlayerState>();
			return false;
		}

		testState->subscribeToPositionUpdate(testRaceUI);

		int arbitraryPositionNumber = 5;
		testState->updatePositionTo(arbitraryPositionNumber);

		int stateCurrentPosition = testState->currentPosition();
		UE_LOG(LogTemp, Log, TEXT("current player state position: %d."), stateCurrentPosition);
		
		int uiCurrentPosition = testRaceUI->currentPosition();
		UE_LOG(LogTemp, Log, TEXT("current race player ui position: %d."), uiCurrentPosition);

		bool positionsMatch = stateCurrentPosition == uiCurrentPosition;

		if(positionsMatch)
		{
			test->TestTrue(test->conditionMessage(), positionsMatch);
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
		return test->manageTickCountTowardsLimit();
	}
	return false;
}


bool FCheckPlayerStateLoadsPlayerRaceUISynchronized::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
	
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		
		ARacePlayerState* testState = sessionUtilities.retrieveFromPIEAnInstanceOf<ARacePlayerState>();
		if(testState == nullptr)
		{
			return false;
		}

		APlayerController* controller = sessionUtilities.retrieveFromPIEAnInstanceOf<APlayerController>();
		
		TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(sessionUtilities.currentPIEWorld(),retrievedWidgets, URacePlayerUI::StaticClass(), false);
		
		URacePlayerUI* testRaceUI = Cast<URacePlayerUI, UUserWidget>(retrievedWidgets.Pop());
		if (testRaceUI == nullptr)
		{
			testState->loadRaceUI(controller);
			return false;
		}

		int stateCurrentLap = testState->currentLap();
		UE_LOG(LogTemp, Log, TEXT("current player state lap: %d."), stateCurrentLap);
		
		int uiCurrentLap = testRaceUI->currentLap();
		UE_LOG(LogTemp, Log, TEXT("current race player ui lap: %d."), uiCurrentLap);

		int stateTotalLaps = testState->totalLaps();
		UE_LOG(LogTemp, Log, TEXT("player state total laps: %d."), stateTotalLaps);
		
		int uiTotalLaps = testRaceUI->totalLaps();
		UE_LOG(LogTemp, Log, TEXT("race player total ui laps: %d."), uiTotalLaps);


		int stateCurrentPosition = testState->currentPosition();
		UE_LOG(LogTemp, Log, TEXT("current player state position: %d."), stateCurrentPosition);
		
		int uiCurrentPosition = testRaceUI->currentPosition();
		UE_LOG(LogTemp, Log, TEXT("current race player ui position: %d."), uiCurrentPosition);

		
		bool positionsMatch = stateCurrentPosition == uiCurrentPosition;
		bool lapsMatch = stateCurrentLap == uiCurrentLap;
		bool totalLapsMatch = stateTotalLaps == uiTotalLaps;

		bool valuesMatch = positionsMatch && lapsMatch && totalLapsMatch;

		if(valuesMatch)
		{
			test->TestTrue(test->conditionMessage(), valuesMatch);
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
		return test->manageTickCountTowardsLimit();
	}
	return false;
}





#endif //WITH_DEV_AUTOMATION_TESTS
