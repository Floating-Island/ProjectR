// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "PrRPlayerControllerTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "PlayerController/ProjectRPlayerController.h"
#include "UI/PauseMenu.h"
#include "GameFramework/GameModeBase.h"


//Test preparation commands:













//Test check commands:



bool FCheckPlayerControllerBringsPauseMenu::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		sessionUtilities.currentPIEWorld()->GetAuthGameMode()->SpawnPlayerController(ENetRole::ROLE_None, FString(""));
		AProjectRPlayerController* testPlayerController = sessionUtilities.retrieveFromPIEAnInstanceOf<AProjectRPlayerController>();

		if(testPlayerController)
		{
			UPauseMenu* testMenu = testPlayerController->loadPauseMenu();
		
			aTest->TestTrue(TEXT("loadPauseMenu should bring the pause menu instance and add it to viewport."), testMenu && testMenu->IsInViewport());
			return true;
		}
	}
	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
