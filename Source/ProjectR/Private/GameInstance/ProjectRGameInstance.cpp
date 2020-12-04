// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/ProjectRGameInstance.h"
#include "UI/MainMenu.h"
#include "UI/SingleplayerMenu.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

UMainMenu* UProjectRGameInstance::loadMainMenu()
{
	UMainMenu* mainMenuInstance = Cast<UMainMenu, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), UMainMenu::StaticClass()));
	if (!mainMenuInstance)
	{
		mainMenu = CreateWidget<UMainMenu>(GetWorld(), mainMenuClass, FName("Main Menu"));
	}
	else
	{
		mainMenu = mainMenuInstance;
	}
	UE_LOG(LogTemp, Log, TEXT("attempting to add main menu to viewport"));
	if (!mainMenu->IsInViewport())
	{
		mainMenu->AddToViewport();
		FInputModeUIOnly inputModeData;
		inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		inputModeData.SetWidgetToFocus(mainMenu->TakeWidget());
		GetFirstLocalPlayerController(GetWorld())->SetInputMode(inputModeData);
	}
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	controller->bShowMouseCursor = true;

	return mainMenu;
}

USingleplayerMenu* UProjectRGameInstance::loadSingleplayerMenu()
{
	USingleplayerMenu* singleplayerMenuInstance = Cast<USingleplayerMenu, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), USingleplayerMenu::StaticClass()));
	if (!singleplayerMenuInstance)
	{
		singleplayerMenu = CreateWidget<USingleplayerMenu>(GetWorld(), singleplayerMenuClass, FName("Singleplayer Menu"));
	}
	else
	{
		singleplayerMenu = singleplayerMenuInstance;
	}
	if (!singleplayerMenu->IsInViewport())
	{
		singleplayerMenu->AddToViewport();
		FInputModeUIOnly inputModeData;
		inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		inputModeData.SetWidgetToFocus(mainMenu->TakeWidget());
		GetFirstLocalPlayerController(GetWorld())->SetInputMode(inputModeData);
	}
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	controller->bShowMouseCursor = true;
	
	return singleplayerMenu;
}

bool UProjectRGameInstance::isMainMenuInViewport()
{
	if(!mainMenu)
	{
		return false;
	}
	return mainMenu->IsInViewport();
}

bool UProjectRGameInstance::isSingleplayerMenuInViewport()
{
	if(!singleplayerMenu)
	{
		return false;
	}
	return singleplayerMenu->IsInViewport();
}
