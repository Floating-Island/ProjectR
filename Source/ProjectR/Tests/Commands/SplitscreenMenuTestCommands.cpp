// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "SplitscreenMenuTestCommands.h"

#include "UI/SplitscreenMenu.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "../Utilities/PIESessionUtilities.h"


//Test preparation commands:



//Test check commands:




bool FCheckSplitscreenMenuClickGoBackRemovesFromViewportCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		if (aSplitscreenMenuInstance == nullptr)
		{
			UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
			aSplitscreenMenuInstance = gameInstance->loadSplitscreenMenu();
			isMenuInstanciated = true;
			return false;
		}

		if (isMenuInstanciated && aSplitscreenMenuInstance->IsInViewport())
		{
			FVector2D goBackButtonCoordinates = aSplitscreenMenuInstance->goBackButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(goBackButtonCoordinates);
			return false;
		}

		aTest->TestTrue(TEXT("The splitscreen menu should be removed from viewport when clicking the go back button."), !aSplitscreenMenuInstance->IsInViewport());
		sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckSplitscreenMenuClickGoBackBringsMainMenuCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		if (aSplitscreenMenuInstance == nullptr)
		{
			aSplitscreenMenuInstance = gameInstance->loadSplitscreenMenu();
			isMenuInstanciated = true;
			return false;
		}

		if (isMenuInstanciated && aSplitscreenMenuInstance->IsInViewport())
		{
			FVector2D goBackButtonCoordinates = aSplitscreenMenuInstance->goBackButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(goBackButtonCoordinates);
			return false;
		}

		if (isMenuInstanciated && !aSplitscreenMenuInstance->IsInViewport())
		{
			aTest->TestTrue(TEXT("The splitscreen menu should change to the main menu when clicking the go back button."), gameInstance->isMainMenuInViewport());
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}

		++aTickCount;
		if (aTickCount > aTickLimit)
		{
			aTest->TestTrue(TEXT("The splitscreen menu should change to the main menu when clicking the go back button."), gameInstance->isMainMenuInViewport());
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}


#endif //WITH_DEV_AUTOMATION_TESTS
