// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "SingleplayerMenuTestCommands.h"
#include "UI/SingleplayerMenu.h"
#include "../Utilities/PIESessionUtilities.h"
#include "GameInstance/ProjectRGameInstance.h"

//Test preparation commands:













//Test check commands:


bool FCheckSingleplayerMenuClickPlayButtonChangesMap::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		bool isInAnotherWorld = !sessionUtilities.currentPIEWorld()->GetMapName().Contains("VoidWorld");

		if (isMenuInstanciated && !isInAnotherWorld)
		{
			FVector2D playButtonCoordinates = singleplayerMenuInstance->playButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(playButtonCoordinates);
		}

		if (singleplayerMenuInstance == nullptr)
		{
			UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
			singleplayerMenuInstance = gameInstance->loadSingleplayerMenu();
			isMenuInstanciated = true;
			return false;
		}

		if (isInAnotherWorld)
		{
			test->TestTrue(TEXT("The singleplayer menu should change the current map when clicking the play button."), isInAnotherWorld);
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}

		++tickCount;
		if (tickCount > tickLimit)
		{
			test->TestTrue(TEXT("The singleplayer menu should change the current map when clicking the play button."), isInAnotherWorld);
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}


bool FCheckSingleplayerMenuClickGoBackRemovesFromViewport::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		if (singleplayerMenuInstance == nullptr)
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
			return false;
		}

		test->TestTrue(TEXT("The singleplayer menu should be removed from viewport when clicking the go back button."), !singleplayerMenuInstance->IsInViewport());
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

		if (singleplayerMenuInstance == nullptr)
		{
			singleplayerMenuInstance = gameInstance->loadSingleplayerMenu();
			isMenuInstanciated = true;
			return false;
		}

		if (isMenuInstanciated && singleplayerMenuInstance->IsInViewport())
		{
			FVector2D goBackButtonCoordinates = singleplayerMenuInstance->goBackButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(goBackButtonCoordinates);
			return false;
		}

		if (isMenuInstanciated && !singleplayerMenuInstance->IsInViewport())
		{
			test->TestTrue(TEXT("The singleplayer menu should change to the main menu when clicking the go back button."), gameInstance->isMainMenuInViewport());
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}

		++tickCount;
		if (tickCount > tickLimit)
		{
			test->TestTrue(TEXT("The singleplayer menu should change to the main menu when clicking the go back button."), gameInstance->isMainMenuInViewport());
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}





#endif //WITH_DEV_AUTOMATION_TESTS
