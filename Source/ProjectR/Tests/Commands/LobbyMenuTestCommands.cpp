// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "LobbyMenuTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "../TestBaseClasses/SimplePIETestBase.h"
#include "UI/LobbyMenu.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/StringHolderButton.h"
#include "GameFramework/GameStateBase.h"
#include "UI/MapSelectorWidget.h"
#include "../Utilities/NetworkedPIESessionUtilities.h"
#include "GameState/LobbyGameState.h"


//Test preparation commands:



//Test check commands:


bool FCheckLobbyMenuClickReturnToMainMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		bool inInitialWorld = sessionUtilities.currentPIEWorld()->GetMapName().Contains(test->initialWorldName());
		
		if (inInitialWorld)
		{
			UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance,UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
			if(menuNeedsInstantiation)
			{
				lobbyInstance = gameInstance->loadLobbyMenu();
				menuNeedsInstantiation = false;
				return false;
			}
			if(lobbyInstance && lobbyInstance->IsInViewport())
			{
				FVector2D returnToMainMenuButtonCoordinates = lobbyInstance->returnButtonAbsoluteCenterPosition();
				sessionUtilities.processEditorClick(returnToMainMenuButtonCoordinates);
				return test->manageTickCountTowardsLimit();
			}
		}
		
		test->TestTrue(test->conditionMessage(), !inInitialWorld);
		sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckLobbyMenuClickSelectMapAndStartRace::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance,UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		bool inInitialWorld = sessionUtilities.currentPIEWorld()->GetMapName().Contains(test->initialWorldName());
		
		if (inInitialWorld)
		{
			if(menuNeedsInstantiation)
			{
				lobbyInstance = gameInstance->loadLobbyMenu();
				menuNeedsInstantiation = false;
				return false;
			}
			if(lobbyInstance && lobbyInstance->IsInViewport())
			{
				if(!hasSelectedMap)
				{
					TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
					UWidgetBlueprintLibrary::GetAllWidgetsOfClass(sessionUtilities.currentPIEWorld(),retrievedWidgets, UStringHolderButton::StaticClass(), false);

					if(retrievedWidgets.Num() == 0)
					{
						return false;
					}
					
					UStringHolderButton* testButton = Cast<UStringHolderButton, UUserWidget>(retrievedWidgets.Pop(true));

					FVector2D mapSelectionButtonCoordinates = testButton->buttonCoordinates();
					sessionUtilities.processEditorClick(mapSelectionButtonCoordinates);
					
					hasSelectedMap = true;
				}
				else
				{
					FVector2D startRaceButtonCoordinates = lobbyInstance->startRaceButtonAbsoluteCenterPosition();
					sessionUtilities.processEditorClick(startRaceButtonCoordinates);
				}
				return test->manageTickCountTowardsLimit();
			}
		}
		
		test->TestTrue(test->conditionMessage(), !inInitialWorld);
		sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckLobbyMenuLoadedByLevelBlueprint::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(sessionUtilities.currentPIEWorld(),retrievedWidgets, ULobbyMenu::StaticClass(), false);

		bool lobbyMenuPresent = retrievedWidgets.Num() == 1;
		
		if(lobbyMenuPresent)
		{
			test->TestTrue(test->conditionMessage(), lobbyMenuPresent);
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
		return test->manageTickCountTowardsLimit();
	}
	return false;
}


bool FCheckLobbyMenuUpdatesPlayersConnected::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(sessionUtilities.currentPIEWorld(),retrievedWidgets, ULobbyMenu::StaticClass(), false);

		ULobbyMenu* testLobby = Cast<ULobbyMenu, UUserWidget>(retrievedWidgets.Pop());
		
		if(testLobby)
		{
			int playersInLobby = testLobby->connectedPlayers();
			UE_LOG(LogTemp, Log, TEXT("Players in lobby: %d"), playersInLobby);

			int playersInGameState = sessionUtilities.currentPIEWorld()->GetGameState()->PlayerArray.Num();
			UE_LOG(LogTemp, Log, TEXT("Players in GameState: %d"), playersInGameState);

			playersQuantityMatch = playersInLobby == playersInGameState;

			UE_LOG(LogTemp, Log, TEXT("players quantity %smatch"), *FString(playersQuantityMatch? "" : "don't "));

			sessionUtilities.spawnInPIEAnInstanceOf<APlayerController>();
			TArray<APlayerController*> players = sessionUtilities.retrieveFromPIEAllInstancesOf<APlayerController>();

			UE_LOG(LogTemp, Log, TEXT("quantity of players spawned: %d"), players.Num());
			for(const auto& player : players)
			{
				sessionUtilities.currentPIEWorld()->GetGameState()->AddPlayerState(player->PlayerState);
			}
			
			test->increaseTickCount();
			if(test->tickCountExceedsLimit())
			{
				test->TestTrue(test->conditionMessage(), playersQuantityMatch);
				sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckClientMapSelectorCollapsed::Update()
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

				TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
				UWidgetBlueprintLibrary::GetAllWidgetsOfClass(clientWorld,retrievedWidgets, UMapSelectorWidget::StaticClass(), false);

				if(retrievedWidgets.Num() > 0)
				{
					UMapSelectorWidget* testSelector = Cast<UMapSelectorWidget, UUserWidget>(retrievedWidgets.Pop());
				
					bool isCollapsed = testSelector->GetVisibility() == ESlateVisibility::Collapsed;

					if(isCollapsed)
					{
						test->TestTrue(test->conditionMessage(), isCollapsed);
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
	}
	return false;
}


//bool FCheckClientMapSelectedReplicates::Update()
//{
//	if(GEditor->IsPlayingSessionInEditor())
//	{
//		FWorldContext serverContext = NetworkedPIESessionUtilities::retrieveServerWorldContext(clientQuantity);
//		UWorld* serverWorld = serverContext.World();
//		if(serverWorld)
//		{
//			FWorldContext clientContext = NetworkedPIESessionUtilities::retrieveClientWorldContext();
//			UWorld* clientWorld = clientContext.World();
//			if(clientWorld)
//			{
//
//				TArray<UUserWidget*> retrievedClientWidgets = TArray<UUserWidget*>();
//				UWidgetBlueprintLibrary::GetAllWidgetsOfClass(clientWorld,retrievedClientWidgets, ULobbyMenu::StaticClass(), false);
//
//				
//				if(retrievedClientWidgets.Num() > 0)
//				{
//					
//						TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
//						UWidgetBlueprintLibrary::GetAllWidgetsOfClass(serverWorld,retrievedWidgets, UStringHolderButton::StaticClass(), false);
//
//						if(retrievedWidgets.Num() > 0 )
//						{
//							UStringHolderButton* testButton = Cast<UStringHolderButton, UUserWidget>(retrievedWidgets.Pop());
//
//							selectedMap = testButton->storedString();
//							FVector2D buttonCenter = FVector2D(0.5f, 0.5f);
//							FVector2D selectedButtonCoordinates = testButton->GetTickSpaceGeometry().GetAbsolutePositionAtCoordinates(buttonCenter);
//
//							PIESessionUtilities sessionUtilities = PIESessionUtilities();
//							TSharedPtr<FGenericWindow> buttonWindow = testButton->GetWorld()->GetGameViewport()->GetWindow()->GetNativeWindow();
//							sessionUtilities.processEditorClickAtWindow(selectedButtonCoordinates, buttonWindow);
//						}
//					
//						
//					TArray<UUserWidget*> retrievedServerWidgets = TArray<UUserWidget*>();
//					UWidgetBlueprintLibrary::GetAllWidgetsOfClass(serverWorld,retrievedServerWidgets, ULobbyMenu::StaticClass(), false);
//
//					ULobbyMenu* testServerMenu = Cast<ULobbyMenu, UUserWidget>(retrievedServerWidgets.Pop());
//
//					ULobbyMenu* testClientMenu = Cast<ULobbyMenu, UUserWidget>(retrievedClientWidgets.Pop());
//
//					UE_LOG(LogTemp, Log, TEXT("Selected map: %s"), *selectedMap);
//
//					FString serverMap = testServerMenu->selectedMap();
//					UE_LOG(LogTemp, Log, TEXT("Server map: %s"), *serverMap);
//
//					FString clientMap = testClientMenu->selectedMap();
//					UE_LOG(LogTemp, Log, TEXT("Client map: %s"), *clientMap);
//
//					bool selectedMapsMatch = serverMap == selectedMap && clientMap == selectedMap;
//
//					if(selectedMapsMatch)
//					{
//						test->TestTrue(test->conditionMessage(), selectedMapsMatch);
//						for(auto context : GEditor->GetWorldContexts())
//						{
//							context.World()->bDebugFrameStepExecution = true;
//						}
//						return true;
//					}
//					return test->manageTickCountTowardsLimit();
//				}
//			}
//		}
//	}
//	return false;
//}


bool FCheckClickingAMapChangesLobbyGameState::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();

		TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(testWorld,retrievedWidgets, UStringHolderButton::StaticClass(), false);

		if(retrievedWidgets.Num() > 0 )
		{
			UStringHolderButton* testButton = Cast<UStringHolderButton, UUserWidget>(retrievedWidgets.Pop());

			selectedMap = testButton->storedString();
			FVector2D buttonCenter = FVector2D(0.5f, 0.5f);
			FVector2D selectedButtonCoordinates = testButton->GetTickSpaceGeometry().GetAbsolutePositionAtCoordinates(buttonCenter);

			TSharedPtr<FGenericWindow> buttonWindow = testButton->GetWorld()->GetGameViewport()->GetWindow()->GetNativeWindow();
			sessionUtilities.processEditorClickAtWindow(selectedButtonCoordinates, buttonWindow);
		}
			
		ALobbyGameState* gameState = sessionUtilities.retrieveFromPIEAnInstanceOf<ALobbyGameState>();

		bool mapsCoincident = gameState->selectedMapName() == selectedMap;

		if(mapsCoincident)
		{
			test->TestTrue(test->conditionMessage(), mapsCoincident);
			testWorld->bDebugFrameStepExecution = true;
			return true;
		}
		return test->manageTickCountTowardsLimit();
	}
	return false;
}









#endif //WITH_DEV_AUTOMATION_TESTS
