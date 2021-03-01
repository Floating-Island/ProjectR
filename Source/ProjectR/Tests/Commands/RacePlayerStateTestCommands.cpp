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
#include "PlayerController/ProjectRPlayerController.h"

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
				int desiredCurrentLap = 5;
				UE_LOG(LogTemp, Log, TEXT("desired current lap: %d."), desiredCurrentLap);

				UE_LOG(LogTemp, Log, TEXT("raceStates size: %d."), raceStates.Num());

				UE_LOG(LogTemp, Log, TEXT("making controllers load the race UI..."));
				for (auto iterator = serverWorld->GetPlayerControllerIterator(); iterator; ++iterator)
				{
					AProjectRPlayerController* controller = Cast<AProjectRPlayerController, APlayerController>(iterator->Get());
					ARacePlayerState* testState = Cast<ARacePlayerState, APlayerState>(controller->PlayerState);
					if(testState == nullptr)
					{
						return false;
					}
					controller->loadRaceUI();
				}
				
				if(raceStates.Num() == 0)
				{
					UE_LOG(LogTemp, Log, TEXT("raceStates is empty..."));
					for (auto iterator = serverWorld->GetPlayerControllerIterator(); iterator; ++iterator)
					{
						ARacePlayerState* testState = Cast<ARacePlayerState, APlayerState>(iterator->Get()->PlayerState);
						if(testState == nullptr)
						{
							UE_LOG(LogTemp, Log, TEXT("player state isn't of type RacePlayerState..."));
							raceStates.Empty();
							break;
						}
						UE_LOG(LogTemp, Log, TEXT("player state is of type RacePlayerState, updating lap and adding it to raceStates..."));
						testState->updateLapTo(desiredCurrentLap);
						raceStates.Add(testState);
					}
					return false;
				}
				
				
				TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
				UWidgetBlueprintLibrary::GetAllWidgetsOfClass(clientWorld,retrievedWidgets, URacePlayerUI::StaticClass(), false);

				if(retrievedWidgets.Num() == 0)
				{
					UE_LOG(LogTemp, Log, TEXT("couldn't find RacePlayerUIs..."));
					return false;
				}
				
				URacePlayerUI* testRaceUI = Cast<URacePlayerUI, UUserWidget>(retrievedWidgets.Pop());
				if (testRaceUI == nullptr)
				{
					UE_LOG(LogTemp, Log, TEXT("retrieved widgets aren't of type RacePlayerUIs..."));
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


bool FCheckServerUpdatesPositionReplicatesToClientRaceUI::Update()
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
				int desiredCurrentPosition = 5;
				UE_LOG(LogTemp, Log, TEXT("desired current position: %d."), desiredCurrentPosition);

				UE_LOG(LogTemp, Log, TEXT("raceStates size: %d."), raceStates.Num());

				UE_LOG(LogTemp, Log, TEXT("making controllers load the race UI..."));
				for (auto iterator = serverWorld->GetPlayerControllerIterator(); iterator; ++iterator)
				{
					AProjectRPlayerController* controller = Cast<AProjectRPlayerController, APlayerController>(iterator->Get());
					ARacePlayerState* testState = Cast<ARacePlayerState, APlayerState>(controller->PlayerState);
					if(testState == nullptr)
					{
						return false;
					}
					controller->loadRaceUI();
				}
				
				if(raceStates.Num() == 0)
				{
					UE_LOG(LogTemp, Log, TEXT("raceStates is empty..."));
					for (auto iterator = serverWorld->GetPlayerControllerIterator(); iterator; ++iterator)
					{
						ARacePlayerState* testState = Cast<ARacePlayerState, APlayerState>(iterator->Get()->PlayerState);
						if(testState == nullptr)
						{
							UE_LOG(LogTemp, Log, TEXT("player state isn't of type RacePlayerState..."));
							raceStates.Empty();
							break;
						}
						UE_LOG(LogTemp, Log, TEXT("player state is of type RacePlayerState, updating position and adding it to raceStates..."));
						testState->updatePositionTo(desiredCurrentPosition);
						raceStates.Add(testState);
					}
					return false;
				}
				
				
				TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
				UWidgetBlueprintLibrary::GetAllWidgetsOfClass(clientWorld,retrievedWidgets, URacePlayerUI::StaticClass(), false);

				if(retrievedWidgets.Num() == 0)
				{
					UE_LOG(LogTemp, Log, TEXT("couldn't find RacePlayerUIs..."));
					return false;
				}
				
				URacePlayerUI* testRaceUI = Cast<URacePlayerUI, UUserWidget>(retrievedWidgets.Pop());
				if (testRaceUI == nullptr)
				{
					UE_LOG(LogTemp, Log, TEXT("retrieved widgets aren't of type RacePlayerUIs..."));
					return false;
				}

				int uiCurrentPosition = testRaceUI->currentPosition();
				UE_LOG(LogTemp, Log, TEXT("current race player ui position: %d."), uiCurrentPosition);

				bool positionsMatch = desiredCurrentPosition == uiCurrentPosition;

				if(positionsMatch)
				{
					test->TestTrue(test->conditionMessage(), positionsMatch);
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


bool FCheckServerUpdatesTotalLapsReplicatesToClientRaceUI::Update()
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
				int desiredTotalLaps = 5;
				UE_LOG(LogTemp, Log, TEXT("desired total lap: %d."), desiredTotalLaps);

				UE_LOG(LogTemp, Log, TEXT("raceStates size: %d."), raceStates.Num());

				UE_LOG(LogTemp, Log, TEXT("making controllers load the race UI..."));
				for (auto iterator = serverWorld->GetPlayerControllerIterator(); iterator; ++iterator)
				{
					AProjectRPlayerController* controller = Cast<AProjectRPlayerController, APlayerController>(iterator->Get());
					ARacePlayerState* testState = Cast<ARacePlayerState, APlayerState>(controller->PlayerState);
					if(testState == nullptr)
					{
						return false;
					}
					controller->loadRaceUI();
				}
				
				if(raceStates.Num() == 0)
				{
					UE_LOG(LogTemp, Log, TEXT("raceStates is empty..."));
					for (auto iterator = serverWorld->GetPlayerControllerIterator(); iterator; ++iterator)
					{
						ARacePlayerState* testState = Cast<ARacePlayerState, APlayerState>(iterator->Get()->PlayerState);
						if(testState == nullptr)
						{
							UE_LOG(LogTemp, Log, TEXT("player state isn't of type RacePlayerState..."));
							raceStates.Empty();
							break;
						}
						UE_LOG(LogTemp, Log, TEXT("player state is of type RacePlayerState, updating lap and adding it to raceStates..."));
						testState->setTotalLapsTo(desiredTotalLaps);
						raceStates.Add(testState);
					}
					return false;
				}
				
				
				TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
				UWidgetBlueprintLibrary::GetAllWidgetsOfClass(clientWorld,retrievedWidgets, URacePlayerUI::StaticClass(), false);

				if(retrievedWidgets.Num() == 0)
				{
					UE_LOG(LogTemp, Log, TEXT("couldn't find RacePlayerUIs..."));
					return false;
				}
				
				URacePlayerUI* testRaceUI = Cast<URacePlayerUI, UUserWidget>(retrievedWidgets.Pop());
				if (testRaceUI == nullptr)
				{
					UE_LOG(LogTemp, Log, TEXT("retrieved widgets aren't of type RacePlayerUIs..."));
					return false;
				}

				int uiTotalLaps = testRaceUI->totalLaps();
				UE_LOG(LogTemp, Log, TEXT("total race player ui lap: %d."), uiTotalLaps);

				bool lapsMatch = desiredTotalLaps == uiTotalLaps;

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
