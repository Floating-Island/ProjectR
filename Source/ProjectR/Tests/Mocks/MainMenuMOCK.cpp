// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuMOCK.h"
#include "InputCoreTypes.h"
#include "Components/Button.h"

void UMainMenuMOCK::focusOnQuitButtonAndPressIt()
{
	UWorld* currentWorld = GetWorld();

	APlayerController* currentController = currentWorld->GetFirstPlayerController();

	currentController->bEnableClickEvents = true;
	
	UE_LOG(LogTemp, Log, TEXT("focus set on quit button"));
	quitButton->SetClickMethod(EButtonClickMethod::DownAndUp);
	quitButton->SetUserFocus(currentController);
	currentController->InputKey(EKeys::LeftMouseButton, EInputEvent::IE_DoubleClick, 0.1f, false);
	UE_LOG(LogTemp, Log, TEXT("double click input made"));
}
