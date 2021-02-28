// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "PrRPlayerControllerTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "PlayerController/ProjectRPlayerController.h"
#include "../Mocks/ProjectRPlayerControllerMOCK.h"
#include "UI/PauseMenu.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerInput.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/RacePlayerUI.h"


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

			test->TestTrue(TEXT("loadPauseMenu should bring the pause menu instance and add it to viewport."), testMenu && testMenu->IsInViewport());
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

			test->TestTrue(TEXT("loadPauseMenu should create only one instance of the pause menu."), testMenu == anotherTestMenu);
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

			test->TestTrue(TEXT("loadPauseMenu should make the controller show the mouse cursor."), testPlayerController->ShouldShowMouseCursor());
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
				test->TestTrue(test->conditionMessage(), testPlayerController->pauseMenuIsInViewport());
				return true;
			}
			return test->manageTickCountTowardsLimit();
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
				return test->manageTickCountTowardsLimit();
			}
			test->TestTrue(test->conditionMessage(), !testPlayerController->pauseMenuIsInViewport() && !testPlayerController->ShouldShowMouseCursor());
			return true;
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
				test->TestTrue(TEXT("loadPauseMenu should pause the game."), gameIsPaused);
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
				test->TestTrue(TEXT("Loading the pause menu when already in viewport unpauses the game."), !UGameplayStatics::IsGamePaused(sessionUtilities.defaultPIEWorld()));
				return true;
			}
		}
	}
	return false;
}


bool FCheckPRPlayerControllerLoadsPlayerStateUI::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		if (testPlayerController == nullptr)
		{
			testPlayerController = sessionUtilities.retrieveFromPIEAnInstanceOf<AProjectRPlayerController>();
			return false;
		}
		 testPlayerController->loadRaceUI();

		TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(sessionUtilities.currentPIEWorld(),retrievedWidgets, URacePlayerUI::StaticClass(), false);

		if(retrievedWidgets.Num() > 0)
		{
			URacePlayerUI* testRaceUI = Cast<URacePlayerUI, UUserWidget>(retrievedWidgets.Pop());		

			if(testRaceUI)
			{
				test->TestNotNull(test->conditionMessage(), testRaceUI);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
			return test->manageTickCountTowardsLimit();
		}
	}
	return false;
}








#endif //WITH_DEV_AUTOMATION_TESTS
