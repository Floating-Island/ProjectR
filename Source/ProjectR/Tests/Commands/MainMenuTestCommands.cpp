// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "MainMenuTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "UI/MainMenu.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "Kismet/GameplayStatics.h"

//Test preparation commands:





//Test check commands:


bool FCheckMainMenuClickQuits::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(UGameplayStatics::GetGameInstance(sessionUtilities.defaultPIEWorld()));
		if (mainMenuInstance == nullptr)
		{
			mainMenuInstance = testInstance->loadMainMenu();
		}

		FVector2D quitCoordinates = mainMenuInstance->quitButtonAbsoluteCenterPosition();
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
		test->TestTrue(TEXT("The main menu should quit the game when clicking the quit button."), hasFinishedRunningPIESession);
		return true;
	}

	++tickCount;
	if (tickCount > tickLimit)
	{
		test->TestTrue(TEXT("The main menu should quit the game when clicking the quit button."), hasFinishedRunningPIESession);
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}

	return false;
}


bool FCheckMainMenuClickSingleplayerRemovesMenuFromViewport::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
	
		if(mainMenuInstance == nullptr)
		{
			UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance,UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
			mainMenuInstance = gameInstance->loadMainMenu();
			isMenuInstanciated = true;
			return false;
		}
		
		if(isMenuInstanciated && mainMenuInstance->IsInViewport())
		{
			FVector2D singleplayerButtonCoordinates = mainMenuInstance->singleplayerButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(singleplayerButtonCoordinates);
			return false;
		}
		
		test->TestTrue(TEXT("The main menu should be removed from viewport when clicking the singleplayer button."), !mainMenuInstance->IsInViewport());
		sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckMainMenuClickSingleplayerBringsSingleplayerMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance,UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
	
		if(mainMenuInstance == nullptr)
		{
			mainMenuInstance = gameInstance->loadMainMenu();
			isMenuInstanciated = true;
			return false;
		}
		
		if(isMenuInstanciated && mainMenuInstance->IsInViewport())
		{
			FVector2D singleplayerButtonCoordinates = mainMenuInstance->singleplayerButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(singleplayerButtonCoordinates);
			return false;
		}
		
		if (isMenuInstanciated && !mainMenuInstance->IsInViewport())
		{
			test->TestTrue(TEXT("The main menu should change to the singleplayer menu when clicking the singleplayer button."), gameInstance->isSingleplayerMenuInViewport());
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}

		++tickCount;
		if (tickCount > tickLimit)
		{
			test->TestTrue(TEXT("The main menu should change to the singleplayer menu when clicking the singleplayer button."), gameInstance->isSingleplayerMenuInViewport());
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}


bool FCheckMainMenuClickLocalMultiplayerRemovesMenuFromViewport::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
	
		if(mainMenuInstance == nullptr)
		{
			UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance,UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
			mainMenuInstance = gameInstance->loadMainMenu();
			isMenuInstanciated = true;
			return false;
		}
		
		if(isMenuInstanciated && mainMenuInstance->IsInViewport())
		{
			FVector2D localMultiplayerButtonCoordinates = mainMenuInstance->localMultiplayerButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(localMultiplayerButtonCoordinates);
			return false;
		}
		
		test->TestTrue(TEXT("The main menu should be removed from viewport when clicking the local multiplayer button."), !mainMenuInstance->IsInViewport());
		sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckSoloMainMenuClickLocalMultiplayerBringsLocalMultiplayerMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance,UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
	
		if(mainMenuInstance == nullptr)
		{
			mainMenuInstance = gameInstance->loadMainMenu();
			isMenuInstanciated = true;
			return false;
		}
		
		if(isMenuInstanciated && mainMenuInstance->IsInViewport())
		{
			FVector2D localMultiplayerButtonCoordinates = mainMenuInstance->localMultiplayerButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(localMultiplayerButtonCoordinates);
			return false;
		}
		
		if (isMenuInstanciated && !mainMenuInstance->IsInViewport())
		{
			test->TestTrue(TEXT("The main menu should change to the local multiplayer menu when clicking the local multiplayer button."), gameInstance->isLocalMultiplayerMenuInViewport());
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}

		++tickCount;
		if (tickCount > tickLimit)
		{
			test->TestTrue(TEXT("The main menu should change to the local multiplayer menu when clicking the local multiplayer button."), gameInstance->isLocalMultiplayerMenuInViewport());
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
	}
	return false;
}


bool FCheckMainMenuClickLanMultiplayerRemovesMenuFromViewport::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
	
		if(mainMenuInstance == nullptr)
		{
			UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance,UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());
			mainMenuInstance = gameInstance->loadMainMenu();
			isMenuInstanciated = true;
			return false;
		}
		
		if(isMenuInstanciated && mainMenuInstance->IsInViewport())
		{
			FVector2D lanMultiplayerButtonCoordinates = mainMenuInstance->lanMultiplayerButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(lanMultiplayerButtonCoordinates);
			return false;
		}
		
		test->TestTrue(TEXT("The main menu should be removed from viewport when clicking the lan multiplayer button."), !mainMenuInstance->IsInViewport());
		sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}
	return false;
}


bool FCheckMainMenuClickLanMultiplayerBringsLanMultiplayerMenu::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance,UGameInstance>(sessionUtilities.defaultPIEWorld()->GetGameInstance());

		bool isLanInViewport = gameInstance->isLanMultiplayerMenuInViewport();
		
		if (isLanInViewport)
		{
			test->TestTrue(test->conditionMessage(), isLanInViewport);
			sessionUtilities.defaultPIEWorld()->bDebugFrameStepExecution = true;
			return true;
		}
		
		if(mainMenuInstance == nullptr)
		{
			mainMenuInstance = gameInstance->loadMainMenu();
			return false;
		}
		
		if(mainMenuInstance->IsInViewport())
		{
			FVector2D lanMultiplayerButtonCoordinates = mainMenuInstance->lanMultiplayerButtonAbsoluteCenterPosition();
			sessionUtilities.processEditorClick(lanMultiplayerButtonCoordinates);
		}
		return test->manageTickCountTowardsLimit();
	}
	return false;
}




#endif //WITH_DEV_AUTOMATION_TESTS
