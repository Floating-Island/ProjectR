// Fill out your copyright notice in the Description page of Project Settings.


#if WITH_DEV_AUTOMATION_TESTS

#include "PauseMenuTestCommands.h"
#include "UI/PauseMenu.h"
#include "../Utilities/PIESessionUtilities.h"
#include "PlayerController/ProjectRPlayerController.h"
#include "GameFramework/GameModeBase.h"

//Test preparation commands:













//Test check commands:


bool FCheckPauseMenuClickReturnButtonChangesToMainMenuMap::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		bool isInAnotherWorld = sessionUtilities.currentPIEWorld()->GetMapName() != "VoidWorld-PlayerController";



		if (aPauseMenuInstance == nullptr)
		{
			sessionUtilities.currentPIEWorld()->GetAuthGameMode()->SpawnPlayerController(ENetRole::ROLE_None, FString(""));
			AProjectRPlayerController* testPlayerController = sessionUtilities.retrieveFromPIEAnInstanceOf<AProjectRPlayerController>();

			if (testPlayerController)
			{
				aPauseMenuInstance = testPlayerController->loadPauseMenu();
			}
			return false;
		}
		else
		{
			if (!isInAnotherWorld)
			{
				FVector2D returnButtonCoordinates = aPauseMenuInstance->returnButtonAbsoluteCenterPosition();
				sessionUtilities.processEditorClick(returnButtonCoordinates);
				return false;
			}

			if (isInAnotherWorld)
			{
				bool inMainMenuMap = sessionUtilities.currentPIEWorld()->GetMapName() == "MainMenu";
				aTest->TestTrue(TEXT("The singleplayer menu should change the current map when clicking the play button."), inMainMenuMap);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}

			++aTickCount;
			if (aTickCount > aTickLimit)
			{
				aTest->TestTrue(TEXT("The singleplayer menu should change the current map when clicking the play button."), isInAnotherWorld);
				sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
				return true;
			}
		}
	}
	return false;
}






#endif //WITH_DEV_AUTOMATION_TESTS
