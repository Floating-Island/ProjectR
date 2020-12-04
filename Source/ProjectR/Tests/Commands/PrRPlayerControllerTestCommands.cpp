// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "PrRPlayerControllerTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "PlayerController/ProjectRPlayerController.h"
#include "../Mocks/ProjectRPlayerControllerMOCK.h"
#include "UI/PauseMenu.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerInput.h"


//Test preparation commands:













//Test check commands:



bool FCheckPlayerControllerBringsPauseMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		sessionUtilities.defaultPIEWorld()->GetAuthGameMode()->SpawnPlayerController(ENetRole::ROLE_None, FString(""));
		AProjectRPlayerController* testPlayerController = sessionUtilities.retrieveFromPIEAnInstanceOf<AProjectRPlayerController>();

		if (testPlayerController)
		{
			UPauseMenu* testMenu = testPlayerController->loadPauseMenu();

			aTest->TestTrue(TEXT("loadPauseMenu should bring the pause menu instance and add it to viewport."), testMenu && testMenu->IsInViewport());
			return true;
		}
	}
	return false;
}


bool FCheckPlayerControllerCreatesUniquePauseMenuInstance::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		sessionUtilities.defaultPIEWorld()->GetAuthGameMode()->SpawnPlayerController(ENetRole::ROLE_None, FString(""));
		AProjectRPlayerController* testPlayerController = sessionUtilities.retrieveFromPIEAnInstanceOf<AProjectRPlayerController>();

		if (testPlayerController)
		{
			UPauseMenu* testMenu = testPlayerController->loadPauseMenu();
			UPauseMenu* anotherTestMenu = testPlayerController->loadPauseMenu();

			aTest->TestTrue(TEXT("loadPauseMenu should create only one instance of the pause menu."), testMenu == anotherTestMenu);
			return true;
		}
	}
	return false;
}


bool FCheckPlayerControllerShowsMouseCursor::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		sessionUtilities.defaultPIEWorld()->GetAuthGameMode()->SpawnPlayerController(ENetRole::ROLE_None, FString(""));
		AProjectRPlayerController* testPlayerController = sessionUtilities.retrieveFromPIEAnInstanceOf<AProjectRPlayerController>();

		if (testPlayerController)
		{
			UPauseMenu* testMenu = testPlayerController->loadPauseMenu();

			aTest->TestTrue(TEXT("loadPauseMenu should make the controller show the mouse cursor."), testPlayerController->ShouldShowMouseCursor());
			return true;
		}
	}
	return false;
}


bool FCheckPlayerControllerPressEscBringsPauseMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		if (testPlayerController == nullptr)
		{
			PIESessionUtilities sessionUtilities = PIESessionUtilities();
			sessionUtilities.defaultPIEWorld()->GetAuthGameMode()->SpawnPlayerController(ENetRole::ROLE_None, FString(""));
			testPlayerController = sessionUtilities.retrieveFromPIEAnInstanceOf<AProjectRPlayerControllerMOCK>();

			return false;
		}
		else
		{
			testPlayerController->InputKey(EKeys::Escape, EInputEvent::IE_Pressed, 5.0f, false);
			
			if (testPlayerController->pauseMenuIsInViewport())
			{
				aTest->TestTrue(TEXT("loadPauseMenu should make the controller show the mouse cursor."), testPlayerController->pauseMenuIsInViewport());
				return true;
			}
		}
	}
	return false;
}






#endif //WITH_DEV_AUTOMATION_TESTS
