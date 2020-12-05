// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/ProjectRPlayerController.h"
#include "UI/PauseMenu.h"
#include "Kismet/GameplayStatics.h"

void AProjectRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindKey(EKeys::Escape, IE_Pressed, this, &AProjectRPlayerController::loadPauseMenuWrapper);
}

AProjectRPlayerController::AProjectRPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bShouldPerformFullTickWhenPaused = true;
}

UPauseMenu* AProjectRPlayerController::loadPauseMenu()
{//if someday there's a crash when bringing up the pause menu, look at the main menu and singleplayer menu instantiation in the game instance.
	if (!pauseMenu || pauseMenu->IsUnreachable())
	{
		pauseMenu = CreateWidget<UPauseMenu>(GetWorld(), pauseMenuClass, FName("Pause Menu"));
	}
	if (!pauseMenu->IsInViewport())
	{
		focusOnPauseMenu();
	}
	else
	{
		focusOnGame(); 
	}

	return pauseMenu;
}

void AProjectRPlayerController::focusOnPauseMenu()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	pauseMenu->AddToViewport();
	FInputModeGameAndUI inputModeData;
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputModeData.SetWidgetToFocus(pauseMenu->TakeWidget());
	SetInputMode(inputModeData);
	bShowMouseCursor = true;
}

void AProjectRPlayerController::focusOnGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	pauseMenu->RemoveFromViewport();
	FInputModeGameOnly inputModeData;
	inputModeData.SetConsumeCaptureMouseDown(true);
	SetInputMode(inputModeData);
	bShowMouseCursor = false;
}

void AProjectRPlayerController::loadPauseMenuWrapper()
{
	loadPauseMenu();
}
