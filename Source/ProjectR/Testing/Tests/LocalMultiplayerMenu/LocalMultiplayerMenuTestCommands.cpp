// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "LocalMultiplayerMenuTestCommands.h"

#include "UI/LocalMultiplayerMenu.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "../../Utilities/PIESessionUtilities.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/StringHolderButton.h"

//Test preparation commands:



//Test check commands:




bool FCheckLocalMultiplayerMenuClickGoBackRemovesFromViewport::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		if (localMultiplayerMenuInstance == nullptr)
		{
			UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
			localMultiplayerMenuInstance = gameInstance->loadLocalMultiplayerMenu();
			isMenuInstanciated = true;
			return false;
		}

		if (isMenuInstanciated && localMultiplayerMenuInstance->IsInViewport())
		{
			FVector2D goBackButtonCoordinates = localMultiplayerMenuInstance->goBackButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(goBackButtonCoordinates);
			return false;
		}

		test->TestTrue(test->conditionMessage(), !localMultiplayerMenuInstance->IsInViewport());
		sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckLocalMultiplayerMenuClickGoBackBringsMainMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		bool mainMenuInViewport = gameInstance->isMainMenuInViewport();

		if(mainMenuInViewport)
		{
			test->TestTrue(test->conditionMessage(), mainMenuInViewport);
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
		
		if (localMultiplayerMenuInstance == nullptr)
		{
			localMultiplayerMenuInstance = gameInstance->loadLocalMultiplayerMenu();
			return false;
		}

		if (localMultiplayerMenuInstance->IsInViewport())
		{
			FVector2D goBackButtonCoordinates = localMultiplayerMenuInstance->goBackButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(goBackButtonCoordinates);
		}

		return test->manageTickCountTowardsLimit();
	}
	return false;
}


bool FCheckLocalMultiplayerMenuClickPlaySetsPlayers::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.currentPIEWorld()->GetGameInstance());
		bool isInInitialWorld = sessionUtilities.currentPIEWorld()->GetMapName().Contains("VoidWorld");//beware of map changes. The current world changes so the menu becomes unavailable...

		if(isInInitialWorld)
		{
			if (localMultiplayerMenuInstance == nullptr)
			{
				localMultiplayerMenuInstance = gameInstance->loadLocalMultiplayerMenu();
				return false;
			}
			if (localMultiplayerMenuInstance->IsInViewport())
			{
				aSelectedNumberOfPlayers = localMultiplayerMenuInstance->selectedPlayerQuantity();
				FVector2D playButtonCoordinates = localMultiplayerMenuInstance->playButtonAbsoluteCenterPosition();
				sessionUtilities.processEditorClick(playButtonCoordinates);
				return false;
			}
		}
		
		bool expectedPlayersAreSelectedPlayersQuantity = gameInstance->necessaryPlayers() == aSelectedNumberOfPlayers;
		if(expectedPlayersAreSelectedPlayersQuantity)
		{
			test->TestTrue(test->conditionMessage(), expectedPlayersAreSelectedPlayersQuantity);
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
		return test->manageTickCountTowardsLimit();
	}
	return false;
}


bool FCheckLocalMultiplayerMenuClickMapAndPlayButtonChangesMap::Update()
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
				localMultiplayerMenuInstance = gameInstance->loadLocalMultiplayerMenu();
				menuNeedsInstantiation = false;
				return false;
			}
			if(localMultiplayerMenuInstance && localMultiplayerMenuInstance->IsInViewport())
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
					FVector2D startRaceButtonCoordinates = localMultiplayerMenuInstance->playButtonAbsoluteCenterPosition();
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



#endif //WITH_DEV_AUTOMATION_TESTS
