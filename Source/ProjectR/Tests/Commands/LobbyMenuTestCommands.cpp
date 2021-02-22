// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "LobbyMenuTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "../TestBaseClasses/SimplePIETestBase.h"
#include "UI/LobbyMenu.h"


//Test preparation commands:



//Test check commands:


bool FCheckLobbyMenuClickReturnToMainMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance,UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		bool inInitialWorld = gameInstance->isLanMultiplayerMenuInViewport();
		
		if (inInitialWorld)
		{
			if(menuNeedsInstantiation)
			{
				lobbyInstance = gameInstance->loadLobbyMenu();
				menuNeedsInstantiation = false;
				return false;
			}
			if(lobbyInstance && lobbyInstance->IsInViewport())
			{
				FVector2D returnToMainMenuButtonCoordinates = lobbyInstance->returnButtonAbsoluteCenterPosition();
				sessionUtilities.processEditorClick(returnToMainMenuButtonCoordinates);
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
