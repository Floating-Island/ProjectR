// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "SingleplayerMenuTestCommands.h"
#include "UI/SingleplayerMenu.h"
#include "../../Utilities/PIESessionUtilities.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/StringHolderButton.h"

//Test preparation commands:













//Test check commands:


bool FCheckSingleplayerMenuClickMapAndPlayButtonChangesMap::Update()
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
				singleplayerMenuInstance = gameInstance->loadSingleplayerMenu();
				menuNeedsInstantiation = false;
				return false;
			}
			if(singleplayerMenuInstance && singleplayerMenuInstance->IsInViewport())
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
					FVector2D startRaceButtonCoordinates = singleplayerMenuInstance->playButtonAbsoluteCenterPosition();
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


bool FCheckSingleplayerMenuClickGoBackRemovesFromViewport::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		if (!isMenuInstanciated && singleplayerMenuInstance == nullptr)
		{
			UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
			singleplayerMenuInstance = gameInstance->loadSingleplayerMenu();
			isMenuInstanciated = true;
			return false;
		}

		if (isMenuInstanciated && singleplayerMenuInstance->IsInViewport())
		{
			FVector2D goBackButtonCoordinates = singleplayerMenuInstance->goBackButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(goBackButtonCoordinates);
			return test->manageTickCountTowardsLimit();
		}

		test->TestTrue(test->conditionMessage(), !singleplayerMenuInstance->IsInViewport());
		sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckSingleplayerMenuClickGoBackBringsMainMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		if (!isMenuInstanciated && singleplayerMenuInstance == nullptr)
		{
			singleplayerMenuInstance = gameInstance->loadSingleplayerMenu();
			isMenuInstanciated = true;
			return false;
		}

		if (isMenuInstanciated && singleplayerMenuInstance->IsInViewport())
		{
			FVector2D goBackButtonCoordinates = singleplayerMenuInstance->goBackButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(goBackButtonCoordinates);
			return test->manageTickCountTowardsLimit();
		}
		test->TestTrue(test->conditionMessage(), gameInstance->isMainMenuInViewport());
		sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
		return true;

	}
	return false;
}





#endif //WITH_DEV_AUTOMATION_TESTS
