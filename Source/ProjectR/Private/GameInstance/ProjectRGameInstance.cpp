// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/ProjectRGameInstance.h"
#include "UI/MainMenu.h"
#include "UI/SoloRaceMenu.h"
#include "Blueprint/UserWidget.h"

UMainMenu* UProjectRGameInstance::loadMainMenu()
{
	if (!mainMenu)
	{
		mainMenu = CreateWidget<UMainMenu>(this, mainMenuClass, FName("Main Menu"));
	}
	if (!mainMenu->IsInViewport())
	{
		mainMenu->AddToViewport();
	}

	//APlayerController* controller = GetWorld()->GetFirstPlayerController();

	//FInputModeUIOnly inputData;
	//inputData.SetWidgetToFocus(mainMenu->TakeWidget());
	//inputData.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

	//controller->SetInputMode(inputData);
	//controller->bShowMouseCursor = true;

	return mainMenu;
}

USoloRaceMenu* UProjectRGameInstance::loadSoloRaceMenu()
{
	if (!soloRaceMenu)
	{
		soloRaceMenu = CreateWidget<USoloRaceMenu>(this, soloRaceMenuClass, FName("Solo Race Menu"));
	}
	if (!soloRaceMenu->IsInViewport())
	{
		soloRaceMenu->AddToViewport();
	}

	return soloRaceMenu;
}

bool UProjectRGameInstance::isMainMenuInViewport()
{
	if(!mainMenu)
	{
		return false;
	}
	return mainMenu->IsInViewport();
}
