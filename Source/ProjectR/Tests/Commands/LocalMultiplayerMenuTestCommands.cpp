// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "LocalMultiplayerMenuTestCommands.h"

#include "UI/LocalMultiplayerMenu.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "../Utilities/PIESessionUtilities.h"


//Test preparation commands:



//Test check commands:




bool FCheckLocalMultiplayerMenuClickGoBackRemovesFromViewportCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		if (aLocalMultiplayerMenuInstance == nullptr)
		{
			UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
			aLocalMultiplayerMenuInstance = gameInstance->loadLocalMultiplayerMenu();
			isMenuInstanciated = true;
			return false;
		}

		if (isMenuInstanciated && aLocalMultiplayerMenuInstance->IsInViewport())
		{
			FVector2D goBackButtonCoordinates = aLocalMultiplayerMenuInstance->goBackButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(goBackButtonCoordinates);
			return false;
		}

		aTest->TestTrue(TEXT("The local multiplayer menu should be removed from viewport when clicking the go back button."), !aLocalMultiplayerMenuInstance->IsInViewport());
		sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckLocalMultiplayerMenuClickGoBackBringsMainMenuCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		if (aLocalMultiplayerMenuInstance == nullptr)
		{
			aLocalMultiplayerMenuInstance = gameInstance->loadLocalMultiplayerMenu();
			isMenuInstanciated = true;
			return false;
		}

		if (isMenuInstanciated && aLocalMultiplayerMenuInstance->IsInViewport())
		{
			FVector2D goBackButtonCoordinates = aLocalMultiplayerMenuInstance->goBackButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(goBackButtonCoordinates);
			return false;
		}

		if (isMenuInstanciated && !aLocalMultiplayerMenuInstance->IsInViewport())
		{
			aTest->TestTrue(TEXT("The local multiplayer menu should change to the main menu when clicking the go back button."), gameInstance->isMainMenuInViewport());
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}

		++aTickCount;
		if (aTickCount > aTickLimit)
		{
			aTest->TestTrue(TEXT("The local multiplayer menu should change to the main menu when clicking the go back button."), gameInstance->isMainMenuInViewport());
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}


bool FCheckLocalMultiplayerMenuClickPlaySetsPlayers::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.currentPIEWorld()->GetGameInstance());
		bool isInInitialWorld = sessionUtilities.currentPIEWorld()->GetMapName().Contains("VoidWorld");

		if(isInInitialWorld)
		{
			if (aLocalMultiplayerMenuInstance == nullptr)
			{
				aLocalMultiplayerMenuInstance = gameInstance->loadLocalMultiplayerMenu();
				return false;
			}
			if (aLocalMultiplayerMenuInstance->IsInViewport())
			{
				aSelectedNumberOfPlayers = aLocalMultiplayerMenuInstance->selectedPlayerQuantity();
				FVector2D playButtonCoordinates = aLocalMultiplayerMenuInstance->playButtonAbsoluteCenterPosition();
				sessionUtilities.processEditorClick(playButtonCoordinates);
				return false;
			}
		}
		
		bool expectedPlayersAreSelectedPlayersQuantity = gameInstance->necessaryPlayers() == aSelectedNumberOfPlayers;
		++aTickCount;
		if (aTickCount > aTickLimit)
		{
			aTest->TestTrue(TEXT("The local multiplayer menu should set the expected players set in the combo box."), expectedPlayersAreSelectedPlayersQuantity);
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
		aTest->TestTrue(TEXT("The local multiplayer menu should set the expected players set in the combo box."), expectedPlayersAreSelectedPlayersQuantity);
		sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FChecklocalMultiplayerMenuClickPlayButtonChangesMapCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		bool isInAnotherWorld = !sessionUtilities.currentPIEWorld()->GetMapName().Contains("VoidWorld");

		if (isMenuInstanciated && !isInAnotherWorld)
		{
			FVector2D playButtonCoordinates = aLocalMultiplayerMenuInstance->playButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(playButtonCoordinates);
		}

		if (aLocalMultiplayerMenuInstance == nullptr)
		{
			UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
			aLocalMultiplayerMenuInstance = gameInstance->loadLocalMultiplayerMenu();
			isMenuInstanciated = true;
			return false;
		}

		if (isInAnotherWorld)
		{
			aTest->TestTrue(TEXT("The local multiplayer menu should change the current map when clicking the play button."), isInAnotherWorld);
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}

		++aTickCount;
		if (aTickCount > aTickLimit)
		{
			aTest->TestTrue(TEXT("The local multiplayer menu should change the current map when clicking the play button."), isInAnotherWorld);
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
