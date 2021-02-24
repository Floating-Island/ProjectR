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

			sessionUtilities.spawnLocalPlayer();
			
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





#endif //WITH_DEV_AUTOMATION_TESTS
