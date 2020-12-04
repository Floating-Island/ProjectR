// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "PauseMenuTestCommands.h"
#include "UI/PauseMenu.h"
#include "../Utilities/PIESessionUtilities.h"
#include "../Mocks/ProjectRPlayerControllerMOCK.h"
#include "PlayerController/ProjectRPlayerController.h"
#include "GameFramework/GameModeBase.h"

//Test preparation commands:













//Test check commands:


bool FCheckPauseMenuClickReturnButtonChangesToMainMenuMap::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		bool isInAnotherWorld = !GEditor->GetPIEWorldContext()->World()->GetMapName().Contains("VoidWorld-PlayerController");

		UE_LOG(LogTemp, Log, TEXT("this is %s world"), *GEditor->GetPIEWorldContext()->World()->GetMapName());

		if (aPauseMenuInstance == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("attempting pause menu instantiation..."));
			sessionUtilities.defaultPIEWorld()->GetAuthGameMode()->SpawnPlayerController(ENetRole::ROLE_None, FString(""));
			AProjectRPlayerController* testPlayerController = sessionUtilities.retrieveFromPIEAnInstanceOf<AProjectRPlayerController>();

			if (testPlayerController)
			{
				UE_LOG(LogTemp, Log, TEXT("controller instantiated, attempting pause menu load..."));
				aPauseMenuInstance = testPlayerController->loadPauseMenu();
			}
			return false;
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("pause menu is instantiated"));
			if (!isInAnotherWorld)
			{
				FVector2D returnButtonCoordinates = aPauseMenuInstance->returnButtonAbsoluteCenterPosition();
				UE_LOG(LogTemp, Log, TEXT("return button coordinates in viewport: %s"), *returnButtonCoordinates.ToString());
				UE_LOG(LogTemp, Log, TEXT("attempting click"));
				sessionUtilities.processEditorClick(returnButtonCoordinates);
				return false;
			}

			if (isInAnotherWorld)
			{
				bool inMainMenuMap = GEditor->GetPIEWorldContext()->World()->GetMapName().Contains("MainMenu");
				aTest->TestTrue(TEXT("The pause menu should change to the main menu map when clicking the return button."), inMainMenuMap);
				sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}

			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				aTest->TestTrue(TEXT("The pause menu should change to the main menu map when clicking the return button."), isInAnotherWorld);
				sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}


bool FCheckPauseMenuClickResumeButtonRemovesMenuAndResumes::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		sessionUtilities.defaultPIEWorld()->GetAuthGameMode()->SpawnPlayerController(ENetRole::ROLE_None, FString(""));
		AProjectRPlayerControllerMOCK* testPlayerController = sessionUtilities.retrieveFromPIEAnInstanceOf<AProjectRPlayerControllerMOCK>();
		
		if (aPauseMenuInstance == nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("attempting pause menu instantiation..."));

			if (testPlayerController)
			{
				UE_LOG(LogTemp, Log, TEXT("controller instantiated, attempting pause menu load..."));
				aPauseMenuInstance = testPlayerController->loadPauseMenu();
			}
			return false;
		}
		else
		{
			bool isPaused = UGameplayStatics::IsGamePaused(sessionUtilities.defaultPIEWorld());
			UE_LOG(LogTemp, Log, TEXT("pause menu is instantiated"));
			if (isPaused)
			{
				FVector2D resumeButtonCoordinates = aPauseMenuInstance->resumeButtonAbsoluteCenterPosition();
				UE_LOG(LogTemp, Log, TEXT("resume button coordinates in viewport: %s"), *resumeButtonCoordinates.ToString());
				UE_LOG(LogTemp, Log, TEXT("attempting click"));
				sessionUtilities.processEditorClick(resumeButtonCoordinates);
				return false;
			}

			bool gameResumedAndNoMenu = !isPaused && !testPlayerController->pauseMenuIsInViewport();
			if (gameResumedAndNoMenu)
			{
				aTest->TestTrue(TEXT("The pause menu should be removed from viewport and reusme the game when clicking on the resume button."), gameResumedAndNoMenu);
				sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}

			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				aTest->TestTrue(TEXT("The pause menu should be removed from viewport and reusme the game when clicking on the resume button."), gameResumedAndNoMenu);
				sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}





#endif //WITH_DEV_AUTOMATION_TESTS
