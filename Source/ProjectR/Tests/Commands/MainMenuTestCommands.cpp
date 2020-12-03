// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "MainMenuTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "UI/MainMenu.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "Kismet/GameplayStatics.h"

//Test preparation commands:





//Test check commands:


bool FCheckMainMenuClickQuitsCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(UGameplayStatics::GetGameInstance(sessionUtilities.defaultPIEWorld()));
		if (aMainMenuInstance == nullptr)
		{
			aMainMenuInstance = testInstance->loadMainMenu();
		}

		FVector2D quitCoordinates = aMainMenuInstance->quitButtonAbsoluteCenterPosition();
		UE_LOG(LogTemp, Log, TEXT("quit button coordinates in viewport: %s"), *quitCoordinates.ToString());

		if (inPIE)//first, the game menu instance has to be rendered correctly. This happens on the next frame.
		{
			//now I make a click in the button pixel position
			sessionUtilities.processEditorClick(quitCoordinates);
		}
		inPIE = true;
	}

	bool hasFinishedRunningPIESession = inPIE && !GEditor->IsPlayingSessionInEditor();

	if (hasFinishedRunningPIESession)
	{
		aTest->TestTrue(TEXT("The main menu should quit the game when clicking the quit button."), hasFinishedRunningPIESession);
		return true;
	}

	++aTickCount;
	if (aTickCount > aTickLimit)
	{
		aTest->TestTrue(TEXT("The main menu should quit the game when clicking the quit button."), hasFinishedRunningPIESession);
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}

	return false;
}


bool FCheckMainMenuClickSinglePlayerRemovesMenuFromViewportCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
	
		if(aMainMenuInstance == nullptr)
		{
			UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance,UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
			aMainMenuInstance = gameInstance->loadMainMenu();
			isMenuInstanciated = true;
			return false;
		}
		
		if(isMenuInstanciated && aMainMenuInstance->IsInViewport())
		{
			FVector2D singleplayerButtonCoordinates = aMainMenuInstance->singleplayerButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(singleplayerButtonCoordinates);
			return false;
		}
		
		aTest->TestTrue(TEXT("The main menu should be removed from viewport when clicking the singleplayer button."), !aMainMenuInstance->IsInViewport());
		sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckSoloMainMenuClickSingleplayerBringsSingleplayerMenuCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance,UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
	
		if(aMainMenuInstance == nullptr)
		{
			aMainMenuInstance = gameInstance->loadMainMenu();
			isMenuInstanciated = true;
			return false;
		}
		
		if(isMenuInstanciated && aMainMenuInstance->IsInViewport())
		{
			FVector2D goBackButtonCoordinates = aMainMenuInstance->singleplayerButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(goBackButtonCoordinates);
			return false;
		}
		
		if (isMenuInstanciated && !aMainMenuInstance->IsInViewport())
		{
			aTest->TestTrue(TEXT("The main menu should change to the solo race menu when clicking the singleplayer button."), gameInstance->isSingleplayerMenuInViewport());
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}

		++aTickCount;
		if (aTickCount > aTickLimit)
		{
			aTest->TestTrue(TEXT("The main menu should change to the solo race menu when clicking the singleplayer button."), gameInstance->isSingleplayerMenuInViewport());
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}




#endif //WITH_DEV_AUTOMATION_TESTS
