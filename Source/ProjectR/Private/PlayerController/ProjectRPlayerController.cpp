// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/ProjectRPlayerController.h"
#include "UI/PauseMenu.h"
#include "Components/Widget.h"

UPauseMenu* AProjectRPlayerController::loadPauseMenu()
{
	if (!pauseMenu)
	{
		pauseMenu = CreateWidget<UPauseMenu>(GetWorld()->GetGameInstance(), pauseMenuClass, FName("Pause Menu"));
	}
	if (!pauseMenu->IsInViewport())
	{
		pauseMenu->AddToViewport();
	}
	bShowMouseCursor = true;

	return pauseMenu;
}
