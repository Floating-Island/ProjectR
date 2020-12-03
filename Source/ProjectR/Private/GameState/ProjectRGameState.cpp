// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/ProjectRGameState.h"
#include "Blueprint/UserWidget.h"
#include "UI/PauseMenu.h"


UPauseMenu* AProjectRGameState::loadPauseMenu()
{
	if (!pauseMenu)
	{
		pauseMenu = CreateWidget<UPauseMenu>(GetWorld()->GetGameInstance(), pauseMenuClass, FName("Pause Menu"));
	}
	if (!pauseMenu->IsInViewport())
	{
		pauseMenu->AddToViewport();
	}
}
