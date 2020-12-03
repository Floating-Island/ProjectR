// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "SingleplayerMenuTestCommands.h"
#include "UI/SingleplayerMenu.h"
#include "../Utilities/PIESessionUtilities.h"
#include "GameInstance/ProjectRGameInstance.h"

//Test preparation commands:













//Test check commands:


bool FCheckSingleplayerMenuClickPlayButtonChangesMapCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		bool isInAnotherWorld = GEditor->GetPIEWorldContext()->World()->GetMapName() != "VoidWorld";

		if (isMenuInstanciated && !isInAnotherWorld)
		{
			FVector2D playButtonCoordinates = aSingleplayerMenuInstance->playButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(playButtonCoordinates);
		}

		if (aSingleplayerMenuInstance == nullptr)
		{
			UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
			aSingleplayerMenuInstance = gameInstance->loadSingleplayerMenu();
			isMenuInstanciated = true;
			return false;
		}

		if (isInAnotherWorld)
		{
			aTest->TestTrue(TEXT("The singleplayer menu should change the current map when clicking the play button."), isInAnotherWorld);
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}

		++aTickCount;
		if (aTickCount > aTickLimit)
		{
			aTest->TestTrue(TEXT("The singleplayer menu should change the current map when clicking the play button."), isInAnotherWorld);
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}


bool FCheckSingleplayerMenuClickGoBackRemovesFromViewportCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		if (aSingleplayerMenuInstance == nullptr)
		{
			UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
			aSingleplayerMenuInstance = gameInstance->loadSingleplayerMenu();
			isMenuInstanciated = true;
			return false;
		}

		if (isMenuInstanciated && aSingleplayerMenuInstance->IsInViewport())
		{
			FVector2D goBackButtonCoordinates = aSingleplayerMenuInstance->goBackButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(goBackButtonCoordinates);
			return false;
		}

		aTest->TestTrue(TEXT("The singleplayer menu should be removed from viewport when clicking the go back button."), !aSingleplayerMenuInstance->IsInViewport());
		sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckSingleplayerMenuClickGoBackBringsMainMenuCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		if (aSingleplayerMenuInstance == nullptr)
		{
			aSingleplayerMenuInstance = gameInstance->loadSingleplayerMenu();
			isMenuInstanciated = true;
			return false;
		}

		if (isMenuInstanciated && aSingleplayerMenuInstance->IsInViewport())
		{
			FVector2D goBackButtonCoordinates = aSingleplayerMenuInstance->goBackButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(goBackButtonCoordinates);
			return false;
		}

		if (isMenuInstanciated && !aSingleplayerMenuInstance->IsInViewport())
		{
			aTest->TestTrue(TEXT("The singleplayer menu should change to the main menu when clicking the go back button."), gameInstance->isMainMenuInViewport());
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}

		++aTickCount;
		if (aTickCount > aTickLimit)
		{
			aTest->TestTrue(TEXT("The singleplayer menu should change to the main menu when clicking the go back button."), gameInstance->isMainMenuInViewport());
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}





#endif //WITH_DEV_AUTOMATION_TESTS
