// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "LobbyGameStateTestCommands.h"
#include "GameState/LobbyGameState.h"
#include "../Utilities/PIESessionUtilities.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../Utilities/NetworkedPIESessionUtilities.h"
#include "UI/LobbyMenu.h"

//Test preparation commands:



//Test check commands:


bool FCheckLobbyGameStateExistsInLobby::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		ALobbyGameState* testLobby = sessionUtilities.retrieveFromPIEAnInstanceOf<ALobbyGameState>();

		bool lobbyGameStatePresent = testLobby != nullptr;
		
		if(lobbyGameStatePresent)
		{
			test->TestTrue(test->conditionMessage(), lobbyGameStatePresent);
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
		return test->manageTickCountTowardsLimit();
	}
	return false;
}


bool FCheckLobbyGameStateUpdatesClientLobbyMenus::Update()
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
				TArray<UUserWidget*> retrievedClientWidgets = TArray<UUserWidget*>();
				UWidgetBlueprintLibrary::GetAllWidgetsOfClass(clientWorld,retrievedClientWidgets, ULobbyMenu::StaticClass(), false);
				
				if(retrievedClientWidgets.Num() > 0)
				{
					ALobbyGameState* testState = Cast<ALobbyGameState, AActor>(UGameplayStatics::GetActorOfClass(serverWorld, ALobbyGameState::StaticClass()));

					if(testState && needsToSelectMap)
					{
						testState->updateSelectedMap(selectedMap);

						needsToSelectMap = false;
						return false;
					}

					ULobbyMenu* testClientMenu = Cast<ULobbyMenu, UUserWidget>(retrievedClientWidgets.Pop());

					UE_LOG(LogTemp, Log, TEXT("Selected map: %s"), *selectedMap);

					FString clientMap = testClientMenu->selectedMap();
					UE_LOG(LogTemp, Log, TEXT("Client map: %s"), *clientMap);

					bool selectedMapsMatch = clientMap == selectedMap;

					if(selectedMapsMatch)
					{
						test->TestTrue(test->conditionMessage(), selectedMapsMatch);
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



#endif //WITH_DEV_AUTOMATION_TESTS
