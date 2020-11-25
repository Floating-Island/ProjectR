// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "MainMenuTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "UI/MainMenu.h"
#include "../Mocks/MainMenuMOCK.h"

//Test preparation commands:

bool FSpawnMainMenuAndPressQuitInPIE::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UMainMenuMOCK* testMenu = CreateWidget<UMainMenuMOCK>(sessionUtilities.currentPIEWorld(), UMainMenu::StaticClass());
		testMenu->AddToViewport();

		testMenu->focusOnQuitButtonAndPressIt();


		return true;
	}
	return false;	
}



//Test check commands:


bool FCheckMainMenuQuitsCommand::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		inPIE = true;
	}

	bool hasFinishedRunningPIESession = inPIE && !GEditor->IsPlayingSessionInEditor();
	
	if(hasFinishedRunningPIESession)
	{
		test->TestTrue(TEXT("The main menu should quit the game when calling quit."), hasFinishedRunningPIESession);
		return true;
	}
	
	++tickCount;
	if(tickCount > tickLimit)
	{
		test->TestTrue(TEXT("The main menu should quit the game when calling quit."), hasFinishedRunningPIESession);
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}
	
	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
