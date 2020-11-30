// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/ProjectRGameInstance.h"
#include "UI/MainMenu.h"
#include "Blueprint/UserWidget.h"

UMainMenu* UProjectRGameInstance::loadMainMenu()
{
	if(!mainMenu)
	{
		mainMenu = CreateWidget<UMainMenu>(this, mainMenuClass, FName("Main Menu"));
	}
	mainMenu->AddToViewport();

	//APlayerController* controller = GetWorld()->GetFirstPlayerController();

	//FInputModeUIOnly inputData;
	//inputData.SetWidgetToFocus(mainMenu->TakeWidget());
	//inputData.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

	//controller->SetInputMode(inputData);
	//controller->bShowMouseCursor = true;
	
	return mainMenu;
}
