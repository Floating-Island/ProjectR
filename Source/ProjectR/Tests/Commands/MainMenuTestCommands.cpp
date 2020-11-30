// Fill out your copyright notice in the Description page of Project Settings.



#if WITH_DEV_AUTOMATION_TESTS

#include "MainMenuTestCommands.h"
#include "../Utilities/PIESessionUtilities.h"
#include "UI/MainMenu.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "InputCoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

//Test preparation commands:





//Test check commands:


bool FCheckMainMenuQuitsCommand::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		
		GEditor->GetPIEViewport()->SetMouse(547, 307);

		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		UProjectRGameInstance* testInstance = Cast<UProjectRGameInstance, UGameInstance>(UGameplayStatics::GetGameInstance(sessionUtilities.currentPIEWorld()));
		if (mainMenuInstance == nullptr)
		{
			mainMenuInstance = testInstance->loadMainMenu();
			sessionUtilities.currentPIEWorld()->GetAuthGameMode()->SpawnPlayerFromSimulate(FVector(0), FRotator(0));//spawns a player controller.
			APlayerController* testController = testInstance->GetFirstLocalPlayerController();
		}

		FVector2D quitCoordinates =/* mainMenuInstance->quitButtonPixelCenterPosition()*/  FVector2D(547, 307);
		UE_LOG(LogTemp, Log, TEXT("quit button coordinates in viewport: %s"), *quitCoordinates.ToString());

		APlayerController* testController = testInstance->GetFirstLocalPlayerController();
		//testInstance->GetGameViewportClient()->MouseEnter(testInstance->GetGameViewportClient()->Viewport, quitCoordinates.X, quitCoordinates.Y);

		//testController->SetMouseLocation(quitCoordinates.X, quitCoordinates.Y);

		//FVector2D mousePosition = FVector2D();
		//bool isAssociated = testController->GetMousePosition(mousePosition.X, mousePosition.Y);

		//UE_LOG(LogTemp, Log, TEXT("a mouse %s associated."), *FString(isAssociated ? "is" : "isn't"));
		//UE_LOG(LogTemp, Log, TEXT("mouse coordinates: %s"), *mousePosition.ToString());

		if(inPIE)
		{
			FVector2D viewportSize = FVector2D();
			sessionUtilities.currentPIEWorld()->GetGameViewport()->GetViewportSize(viewportSize);
			UE_LOG(LogTemp, Log, TEXT("Viewport size: %s"), *viewportSize.ToString());
			


			//Get our slate application
			FSlateApplication& SlateApp = FSlateApplication::Get();

			const TSet<FKey> pressedButtons = TSet<FKey>({ EKeys::LeftMouseButton });

			FPointerEvent mouseDownEvent(
                0,
                SlateApp.CursorPointerIndex,
                quitCoordinates,
                FVector2D(0, 0),
                pressedButtons,
                EKeys::LeftMouseButton,
                0,
                SlateApp.GetPlatformApplication()->GetModifierKeys()
            );


			//send the mouse event to the slate handler
			TSharedPtr<FGenericWindow> GenWindow;
			UE_LOG(LogTemp, Log, TEXT("Attempting a mouse move:"));
			bool mouseMove = SlateApp.ProcessMouseMoveEvent(mouseDownEvent);
			UE_LOG(LogTemp, Log, TEXT("a mouse move %s been done."), *FString(mouseMove ? "has" : "hasn't"));
			bool mouseClick = SlateApp.ProcessMouseButtonDoubleClickEvent(GenWindow, mouseDownEvent);
			UE_LOG(LogTemp, Log, TEXT("a mouse click %s been done."), *FString(mouseClick ? "has" : "hasn't"));
		}
		inPIE = true;
	}

	bool hasFinishedRunningPIESession = inPIE && !GEditor->IsPlayingSessionInEditor();

	if (hasFinishedRunningPIESession)
	{
		test->TestTrue(TEXT("The main menu should quit the game when pressing the quit button."), hasFinishedRunningPIESession);
		return true;
	}

	++tickCount;
	if (tickCount > tickLimit)
	{
		test->TestTrue(TEXT("The main menu should quit the game when pressing the quit button."), hasFinishedRunningPIESession);
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		sessionUtilities.currentPIEWorld()->bDebugFrameStepExecution = true;
		return true;
	}

	return false;
}



#endif //WITH_DEV_AUTOMATION_TESTS
