// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuMOCK.h"
#include "InputCoreTypes.h"
#include "Components/Button.h"

void UMainMenuMOCK::focusOnQuitButtonAndPressIt()
{
	UWorld* currentWorld = GetWorld();

	quitButton->SetFocus();
	
	currentWorld->GetFirstPlayerController()->InputKey(EKeys::LeftMouseButton, EInputEvent::IE_DoubleClick, 0.0f, false);
}
