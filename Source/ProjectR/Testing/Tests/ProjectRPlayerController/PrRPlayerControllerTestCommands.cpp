// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "PrRPlayerControllerTestCommands.h"
#include "../../Utilities/PIESessionUtilities.h"
#include "PlayerController/ProjectRPlayerController.h"
#include "../../Mocks/ProjectRPlayerControllerMOCK.h"
#include "UI/PauseMenu.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerInput.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/RacePlayerUI.h"
#include "PlayerState/RacePlayerState.h"
#include "../../Utilities/NetworkedPIESessionUtilities.h"
#include "UI/AnnouncerUI.h"
#include "UI/RaceResultsUI.h"


//Test preparation commands:


bool FServerLoadAnnouncers::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		FWorldContext serverContext = NetworkedPIESessionUtilities::retrieveServerWorldContext(clientQuantity);
		UWorld* serverWorld = serverContext.World();
		if(serverWorld)
		{
			FWorldContext clientContext = NetworkedPIESessionUtilities::retrieveClientWorldContext();
			UWorld* clientWorld = clientContext.World();
			if(clientWorld)
			{
				TArray<AActor*> retrievedActors = TArray<AActor*>();
				UGameplayStatics::GetAllActorsOfClass(serverWorld, AProjectRPlayerController::StaticClass(), retrievedActors);
				for(auto& actor : retrievedActors)
				{
					AProjectRPlayerController* controller = Cast<AProjectRPlayerController, AActor>(actor);
					controller->loadAnnouncerUI();
				}
				return true;
			}
		}
	}
	return false;
}


bool FServerLoadResults::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		FWorldContext serverContext = NetworkedPIESessionUtilities::retrieveServerWorldContext(clientQuantity);
		UWorld* serverWorld = serverContext.World();
		if(serverWorld)
		{
			FWorldContext clientContext = NetworkedPIESessionUtilities::retrieveClientWorldContext();
			UWorld* clientWorld = clientContext.World();
			if(clientWorld)
			{
				TArray<AActor*> retrievedActors = TArray<AActor*>();
				UGameplayStatics::GetAllActorsOfClass(serverWorld, AProjectRPlayerController::StaticClass(), retrievedActors);
				for(auto& actor : retrievedActors)
				{
					AProjectRPlayerController* controller = Cast<AProjectRPlayerController, AActor>(actor);
					controller->loadResultsUI();
				}
				return true;
			}
		}
	}
	return false;
}


bool FPlayerControllerLoadResultsUI::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();
		
		TArray<AActor*> retrievedActors = TArray<AActor*>();
		UGameplayStatics::GetAllActorsOfClass(testWorld, AProjectRPlayerController::StaticClass(), retrievedActors);
		if(retrievedActors.Num() > 0)
		{
			for(auto& actor : retrievedActors)
			{
				AProjectRPlayerController* controller = Cast<AProjectRPlayerController, AActor>(actor);
				controller->loadResultsUI();
			}
			return true;
		}
	}
	return false;
}











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


bool FCheckPRPlayerControllerLoadsPlayerRaceUISynchronized::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
	
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		if(testPlayerController == nullptr)
		{
			testPlayerController = sessionUtilities.retrieveFromPIEAnInstanceOf<AProjectRPlayerController>();
			testPlayerController->loadRaceUI();
			return false;
		}
		
		ARacePlayerState* testState = sessionUtilities.retrieveFromPIEAnInstanceOf<ARacePlayerState>();
		if(testState == nullptr)
		{
			return false;
		}
		
		TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(sessionUtilities.currentPIEWorld(),retrievedWidgets, URacePlayerUI::StaticClass(), false);

		if(retrievedWidgets.Num() == 0)
		{
			AProjectRPlayerController* controller = sessionUtilities.retrieveFromPIEAnInstanceOf<AProjectRPlayerController>();
			controller->loadRaceUI();
			return false;
		}
		
		URacePlayerUI* testRaceUI = Cast<URacePlayerUI, UUserWidget>(retrievedWidgets.Pop());
		if (testRaceUI == nullptr)
		{
			return false;
		}

		int stateCurrentLap = testState->currentLap();
		UE_LOG(LogTemp, Log, TEXT("current player state lap: %d."), stateCurrentLap);
		
		int uiCurrentLap = testRaceUI->currentLap();
		UE_LOG(LogTemp, Log, TEXT("current race player ui lap: %d."), uiCurrentLap);

		int stateTotalLaps = testState->totalLaps();
		UE_LOG(LogTemp, Log, TEXT("player state total laps: %d."), stateTotalLaps);
		
		int uiTotalLaps = testRaceUI->totalLaps();
		UE_LOG(LogTemp, Log, TEXT("race player total ui laps: %d."), uiTotalLaps);


		int stateCurrentPosition = testState->currentPosition();
		UE_LOG(LogTemp, Log, TEXT("current player state position: %d."), stateCurrentPosition);
		
		int uiCurrentPosition = testRaceUI->currentPosition();
		UE_LOG(LogTemp, Log, TEXT("current race player ui position: %d."), uiCurrentPosition);

		
		bool positionsMatch = stateCurrentPosition == uiCurrentPosition;
		bool lapsMatch = stateCurrentLap == uiCurrentLap;
		bool totalLapsMatch = stateTotalLaps == uiTotalLaps;

		bool valuesMatch = positionsMatch && lapsMatch && totalLapsMatch;

		if(valuesMatch)
		{
			test->TestTrue(test->conditionMessage(), valuesMatch);
			sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
		return test->manageTickCountTowardsLimit();
	}
	return false;
}


bool FCheckServerRemoveAnnouncerUIRemovesFromClient::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		FWorldContext serverContext = NetworkedPIESessionUtilities::retrieveServerWorldContext(clientQuantity);
		UWorld* serverWorld = serverContext.World();
		if(serverWorld)
		{
			FWorldContext clientContext = NetworkedPIESessionUtilities::retrieveClientWorldContext();
			UWorld* clientWorld = clientContext.World();
			if(clientWorld)
			{
				TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
				UWidgetBlueprintLibrary::GetAllWidgetsOfClass(clientWorld,retrievedWidgets, UAnnouncerUI::StaticClass(), false);

				bool needsToRemoveAnnouncers = false;
				for(const auto& announcer : retrievedWidgets)
				{
					if(announcer->IsInViewport())
					{
						needsToRemoveAnnouncers = true;
						break;
					}
				}
				bool foundAnnouncers = retrievedWidgets.Num() > 0;
				
				if(foundAnnouncers && needsToRemoveAnnouncers)
				{
					TArray<AActor*> retrievedActors = TArray<AActor*>();
					UGameplayStatics::GetAllActorsOfClass(serverWorld, AProjectRPlayerController::StaticClass(), retrievedActors);
					for(auto& actor : retrievedActors)
					{
						AProjectRPlayerController* controller = Cast<AProjectRPlayerController, AActor>(actor);
						controller->removeAnnouncerUI();
					}
				}

				bool hasHiddenAllAnnouncers = foundAnnouncers && !needsToRemoveAnnouncers;

				if(hasHiddenAllAnnouncers)
				{
					test->TestTrue(test->conditionMessage(), hasHiddenAllAnnouncers);
					for(auto context : GEditor->GetWorldContexts())
					{
						context.World()->bDebugFrameStepExecution = true;
					}
					return true;
				}
				return test->manageTickCountTowardsLimit();
			}
		}
	}
	return false;
}


bool FCheckClientLoadsResults::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		FWorldContext serverContext = NetworkedPIESessionUtilities::retrieveServerWorldContext(clientQuantity);
		UWorld* serverWorld = serverContext.World();
		if(serverWorld)
		{
			FWorldContext clientContext = NetworkedPIESessionUtilities::retrieveClientWorldContext();
			UWorld* clientWorld = clientContext.World();
			if(clientWorld)
			{
				TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
				UWidgetBlueprintLibrary::GetAllWidgetsOfClass(clientWorld,retrievedWidgets, URaceResultsUI::StaticClass(), false);

				bool hasLoadedResults = retrievedWidgets.Num() > 0;

				if(hasLoadedResults)
				{
					test->TestTrue(test->conditionMessage(), hasLoadedResults);
					for(auto context : GEditor->GetWorldContexts())
					{
						context.World()->bDebugFrameStepExecution = true;
					}
					return true;
				}
				return test->manageTickCountTowardsLimit();
			}
		}
	}
	return false;
}


bool FCheckPlayerControllerDisablesInput::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UWorld* testWorld = sessionUtilities.currentPIEWorld();

		TArray<UUserWidget*> retrievedWidgets = TArray<UUserWidget*>();
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(testWorld,retrievedWidgets, URaceResultsUI::StaticClass(), false);

		bool hasLoadedResults = retrievedWidgets.Num() > 0;

		if(hasLoadedResults)		
		{
			TArray<AActor*> retrievedActors = TArray<AActor*>();
			UGameplayStatics::GetAllActorsOfClass(testWorld, AProjectRPlayerController::StaticClass(), retrievedActors);

			bool hasInputDisabled = true;
			for(auto& actor : retrievedActors)
			{
				AProjectRPlayerController* controller = Cast<AProjectRPlayerController, AActor>(actor);
				if(controller->InputEnabled())
				{
					hasInputDisabled = false;
					break;
				}
			}

			if(hasInputDisabled)
			{
				test->TestTrue(test->conditionMessage(), hasLoadedResults);
				testWorld->bDebugFrameStepExecution = true;
				return true;
			}	
			return test->manageTickCountTowardsLimit();
		}
	}
	return false;
}







#endif //WITH_DEV_AUTOMATION_TESTS
