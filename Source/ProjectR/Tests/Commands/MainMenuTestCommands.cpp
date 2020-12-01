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
		GEditor->GetPIEViewport()->SetMouse(547, 307);

		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(UGameplayStatics::GetGameInstance(sessionUtilities.currentPIEWorld()));
		if (aMainMenuInstance == nullptr)
		{
			aMainMenuInstance = testInstance->loadMainMenu();
		}

		FVector2D quitCoordinates = aMainMenuInstance->quitButtonAbsouluteCenterPosition();
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
		sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}

	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
