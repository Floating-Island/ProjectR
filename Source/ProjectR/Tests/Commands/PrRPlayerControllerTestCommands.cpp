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
		}
		else
		{
			testPlayerController->InputKey(EKeys::Escape, EInputEvent::IE_Pressed, 5.0f, false);

			if (testPlayerController->pauseMenuIsInViewport())
			{
				aTest->TestTrue(TEXT("Esc key makes the controller load the pause menu."), testPlayerController->pauseMenuIsInViewport());
				return true;
			}
		}
	}
	return false;
}


bool FCheckPlayerControllerPressEscRemovesPauseMenuInViewport::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		if (testPlayerController == nullptr)
		{
			PIESessionUtilities sessionUtilities = PIESessionUtilities();
			sessionUtilities.defaultPIEWorld()->GetAuthGameMode()->SpawnPlayerController(ENetRole::ROLE_None, FString(""));
			testPlayerController = sessionUtilities.retrieveFromPIEAnInstanceOf<AProjectRPlayerControllerMOCK>();
			testPlayerController->loadPauseMenu();
		}
		else
		{
			if (testPlayerController->pauseMenuIsInViewport())
			{
				testPlayerController->InputKey(EKeys::Escape, EInputEvent::IE_Pressed, 5.0f, false);
			}
			else
			{
				aTest->TestTrue(TEXT("Esc key makes the controller remove the pause menu present in viewport and hide the mouse cursor."), !testPlayerController->pauseMenuIsInViewport() && !testPlayerController->ShouldShowMouseCursor());
				return true;
			}
		}
	}
	return false;
}


bool FCheckPlayerControllerLoadPauseMenuPausesTheGame::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		sessionUtilities.defaultPIEWorld()->GetAuthGameMode()->SpawnPlayerController(ENetRole::ROLE_None, FString(""));
		testPlayerController = sessionUtilities.retrieveFromPIEAnInstanceOf<AProjectRPlayerControllerMOCK>();

		if (testPlayerController)
		{
			bool gameIsPaused = UGameplayStatics::IsGamePaused(sessionUtilities.defaultPIEWorld());
			if (!gameIsPaused)
			{
				UPauseMenu* testMenu = testPlayerController->loadPauseMenu();
			}
			else
			{
				aTest->TestTrue(TEXT("loadPauseMenu should pause the game."), gameIsPaused);
				return true;
			}
		}
	}
	return false;
}


bool FCheckPlayerControllerLoadPauseMenuUnPausesTheGameIfInViewport::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		if (testPlayerController == nullptr)
		{
			sessionUtilities.defaultPIEWorld()->GetAuthGameMode()->SpawnPlayerController(ENetRole::ROLE_None, FString(""));
			testPlayerController = sessionUtilities.retrieveFromPIEAnInstanceOf<AProjectRPlayerControllerMOCK>();
			testPlayerController->loadPauseMenu();
		}
		else
		{
			if (testPlayerController->pauseMenuIsInViewport())
			{
				testPlayerController->loadPauseMenu();
			}
			else
			{
				aTest->TestTrue(TEXT("Loading the pause menu when already in viewport unpauses the game."), !UGameplayStatics::IsGamePaused(sessionUtilities.defaultPIEWorld()));
				return true;
			}
		}
	}
	return false;
}








#endif //WITH_DEV_AUTOMATION_TESTS
