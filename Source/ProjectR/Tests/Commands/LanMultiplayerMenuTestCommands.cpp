// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "LanMultiplayerMenuTestCommands.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "../Utilities/PIESessionUtilities.h"

#include "UI/LanMultiplayerMenu.h"


//Test preparation commands:



//Test check commands:



bool FCheckLanMultiplayerMenuClickGoBackRemovesFromViewport::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		if (lanMultiplayerMenuInstance == nullptr)
		{
			UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
			lanMultiplayerMenuInstance = gameInstance->loadLANMUltiplayerMenu();
			return false;
		}

		if(lanMultiplayerMenuInstance->IsInViewport())
		{
			FVector2D goBackButtonCoordinates = lanMultiplayerMenuInstance->goBackButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(goBackButtonCoordinates);
			return false;
		}

		test->TestTrue(TEXT("The lan multiplayer menu should be removed from viewport when clicking the go back button."), !lanMultiplayerMenuInstance->IsInViewport());
		sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckLanMultiplayerMenuClickGoBackBringsMainMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		if (lanMultiplayerMenuInstance == nullptr)
		{
			lanMultiplayerMenuInstance = gameInstance->loadLANMUltiplayerMenu();
			return false;
		}

		if (lanMultiplayerMenuInstance->IsInViewport())
		{
			FVector2D goBackButtonCoordinates = lanMultiplayerMenuInstance->goBackButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(goBackButtonCoordinates);
			return false;
		}

		if (gameInstance->isMainMenuInViewport())
		{
			test->TestTrue(test->conditionMessage(), gameInstance->isMainMenuInViewport());
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}

		return test->manageTickCountTowardsLimit();
	}
	return false;
}


bool FCheckLanMultiplayerMenuClickCreateSessionBringsLobby::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		bool inTestWorld = sessionUtilities.currentPIEWorld()->GetMapName().Contains("VoidWorld");

		if(inTestWorld)
		{
			if (lanMultiplayerMenuInstance == nullptr)
			{
				lanMultiplayerMenuInstance = gameInstance->loadLANMUltiplayerMenu();
				return false;
			}

			if (IsValid(lanMultiplayerMenuInstance) && lanMultiplayerMenuInstance->IsInViewport())
			{
				FVector2D createSessionButtonCoordinates = lanMultiplayerMenuInstance->createSessionButtonAbsoluteCenterPosition();
				sessionUtilities.processEditorClick(createSessionButtonCoordinates);
			}
			return test->manageTickCountTowardsLimit();
		}

		test->TestTrue(test->conditionMessage(), !inTestWorld);
		gameInstance->destroyOnlineSession();
		sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}




#endif //WITH_DEV_AUTOMATION_TESTS
