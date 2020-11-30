// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "MainMenuTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "UI/MainMenu.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "InputCoreTypes.h"

//Test preparation commands:





//Test check commands:


bool FCheckMainMenuClickQuitsCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		GEditor->GetPIEViewport()->SetMouse(547, 307);

		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(UGameplayStatics::GetGameInstance(sessionUtilities.currentPIEWorld()));
		if (mainMenuInstance == nullptr)
		{
			mainMenuInstance = testInstance->loadMainMenu();
		}

		FVector2D quitCoordinates = mainMenuInstance->quitButtonAbsouluteCenterPosition();
		UE_LOG(LogTemp, Log, TEXT("quit button coordinates in viewport: %s"), *quitCoordinates.ToString());

		if (inPIE)//first, the game menu instance has to be rendered correctly. This happens on the next frame.
		{
			//now I make a click in the button pixel position

			//Get our slate application
			FSlateApplication& slateApplication = FSlateApplication::Get();

			const TSet<FKey> pressedButtons = TSet<FKey>({ EKeys::LeftMouseButton });

			FPointerEvent mouseMoveAndClickEvent(
				0,
				slateApplication.CursorPointerIndex,
				quitCoordinates,
				FVector2D(0, 0),
				pressedButtons,
				EKeys::LeftMouseButton,
				0,
				slateApplication.GetPlatformApplication()->GetModifierKeys()
			);
			TSharedPtr<FGenericWindow> genericWindow;
			/*
			 *It's not necessary to move before clicking because when using process mouse button double click, it also moves the cursor to the desired position.
			 *UE_LOG(LogTemp, Log, TEXT("Attempting a mouse move:"));
			 *bool mouseMove = SlateApp.ProcessMouseMoveEvent(mouseMoveAndClickEvent);
			 *UE_LOG(LogTemp, Log, TEXT("a mouse move %s been done."), *FString(mouseMove ? "has" : "hasn't"));
			*/
			UE_LOG(LogTemp, Log, TEXT("Attempting click at coordinates: %s."), *quitCoordinates.ToString());
			bool mouseClick = slateApplication.ProcessMouseButtonDoubleClickEvent(genericWindow, mouseMoveAndClickEvent);
			UE_LOG(LogTemp, Log, TEXT("a mouse click %s been done."), *FString(mouseClick ? "has" : "hasn't"));
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
		sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}

	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
