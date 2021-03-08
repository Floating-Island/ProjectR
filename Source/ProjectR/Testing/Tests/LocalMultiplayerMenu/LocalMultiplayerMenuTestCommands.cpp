// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "LocalMultiplayerMenuTestCommands.h"

#include "UI/LocalMultiplayerMenu.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "../../Utilities/PIESessionUtilities.h"


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


bool FChecklocalMultiplayerMenuClickPlayButtonChangesMap::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		bool isInAnotherWorld = !sessionUtilities.currentPIEWorld()->GetMapName().Contains("VoidWorld");

		if (isMenuInstanciated && !isInAnotherWorld)
		{
			FVector2D playButtonCoordinates = localMultiplayerMenuInstance->playButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(playButtonCoordinates);
		}

		if (localMultiplayerMenuInstance == nullptr)
		{
			UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
			localMultiplayerMenuInstance = gameInstance->loadLocalMultiplayerMenu();
			isMenuInstanciated = true;
			return false;
		}

		if (isInAnotherWorld)
		{
			test->TestTrue(test->conditionMessage(), isInAnotherWorld);
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}

		return test->manageTickCountTowardsLimit();
	}
	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
