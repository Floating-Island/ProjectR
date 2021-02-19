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

		if (isInAnotherWorld)
		{
			test->TestTrue(test->conditionMessage(), isInAnotherWorld);
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
		
		if (isMenuInstanciated && !isInAnotherWorld)
		{
			FVector2D playButtonCoordinates = singleplayerMenuInstance->playButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(playButtonCoordinates);
			return test->manageTickCountTowardsLimit();
		}

		if (!isMenuInstanciated && singleplayerMenuInstance == nullptr)
		{
			UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
			singleplayerMenuInstance = gameInstance->loadSingleplayerMenu();
			isMenuInstanciated = true;
			return false;
		}
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
