// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "MainMenuTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "UI/MainMenu.h"
#include "GameInstance/ProjectRGameInstance.h"


//Test preparation commands:





//Test check commands:


bool FCheckMainMenuQuitsCommand::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		inPIE = true;
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(UGameplayStatics::GetGameInstance(sessionUtilities.currentPIEWorld()));
		if(mainMenuInstance == nullptr)
		{
			mainMenuInstance = testInstance->loadMainMenu();
		}
		mainMenuInstance->quit();
	}

	bool hasFinishedRunningPIESession = inPIE && !GEditor->IsPlayingSessionInEditor();
	
	if(hasFinishedRunningPIESession)
	{
		test->TestTrue(TEXT("The main menu should quit the game when using quit."), hasFinishedRunningPIESession);
		return true;
	}
	
	++tickCount;
	if(tickCount > tickLimit)
	{
		test->TestTrue(TEXT("The main menu should quit the game when using quit."), hasFinishedRunningPIESession);
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}
	
	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
