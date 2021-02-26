// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "RacePlayerStateTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "../TestBaseClasses/SimplePIETestBase.h"
#include "../Utilities/BlueprintWidgetContainerPawn.h"
#include "PlayerState/RacePlayerState.h"
#include "UI/RacePlayerUI.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../Utilities/NetworkedPIESessionUtilities.h"

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


bool FCheckServerUpdatesLapReplicatesToClientRaceUI::Update()
{
		if(GEditor->IsPlayingSessionInEditor())
	{
			FWorldContext serverContext = NetworkedPIESessionUtilities::retrieveServerWorldContext(clientQuantity);
			UWorld* serverWorld = serverContext.World();
			if(serverWorld)
			{
				FWorldContext clientContext = NetworkedPIESessionUtilities::retrieveClientWorldContext();
				UWorld* clientWorld = clientContext.World();
				if(clientWorld)
				{
					if(raceStates.Num() == 0)
					{
						UE_LOG(LogTemp, Log, TEXT("raceStates is empty..."));
						TArray<AActor*> retrievedActors = TArray<AActor*>();
						UGameplayStatics::GetAllActorsOfClass(serverWorld, ARacePlayerState::StaticClass(), retrievedActors);

						for(auto& actor : retrievedActors)
						{
							UE_LOG(LogTemp, Log, TEXT("filling raceStates..."));
							ARacePlayerState* testState = Cast<ARacePlayerState, AActor>(actor);
							if(testState == nullptr)
							{
								UE_LOG(LogTemp, Log, TEXT("player state isn't a RacePlayerState..."));
								return false;
							}
							UE_LOG(LogTemp, Log, TEXT("adding race player state to raceStates..."));
							raceStates.Add(testState);
						}
					}


					int desiredCurrentLap = 5;
					
					UE_LOG(LogTemp, Log, TEXT("desired current lap: %d."), desiredCurrentLap);
					
					for(auto& racePlayerState : raceStates)
					{
						racePlayerState->updateLapTo(5);
					}
					
					
					TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
					UWidgetBlueprintLibrary::GetAllWidgetsOfClass(clientWorld,retrievedWidgets, URacePlayerUI::StaticClass(), false);
					
					URacePlayerUI* testRaceUI = Cast<URacePlayerUI, UUserWidget>(retrievedWidgets.Pop());
					if (testRaceUI == nullptr)
					{
						return false;
					}

					int uiCurrentLap = testRaceUI->currentLap();
					UE_LOG(LogTemp, Log, TEXT("current race player ui lap: %d."), uiCurrentLap);

					bool lapsMatch = desiredCurrentLap == uiCurrentLap;

					if(lapsMatch)
					{
						test->TestTrue(test->conditionMessage(), lapsMatch);
						for(auto context : GEditor->GetWorldContexts())
						{
							context.World()->bDebugFrameStepExecution = true;
						}
						return true;
					}
					return test->manageTickCountTowardsLimit();
				}
			}
		}
	return false;
}





#endif //WITH_DEV_AUTOMATION_TESTS
