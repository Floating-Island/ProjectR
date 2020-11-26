// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "MainMenuTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "UI/MainMenu.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "InputCoreTypes.h"

//Test preparation commands:

bool FSpawnMainMenuAndPressQuitInPIE::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(UGameplayStatics::GetGameInstance(sessionUtilities.currentPIEWorld()));
		UMainMenu* testMenu = testInstance->loadMainMenu();

		FVector2D quitCoordinates = testMenu->quitButtonPosition();

		APlayerController* testController = sessionUtilities.currentPIEWorld()->GetFirstPlayerController();
		testController->SetMouseLocation(quitCoordinates.X, quitCoordinates.Y);
		testController->InputKey(EKeys::LeftMouseButton, EInputEvent::IE_DoubleClick, 0.1f, false);

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
		test->TestTrue(TEXT("The main menu should quit the game when pressing the quit button."), hasFinishedRunningPIESession);
		return true;
	}
	
	++tickCount;
	if(tickCount > tickLimit)
	{
		test->TestTrue(TEXT("The main menu should quit the game when pressing the quit button."), hasFinishedRunningPIESession);
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}
	
	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
