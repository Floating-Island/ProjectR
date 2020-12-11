// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/ProjectRGameInstance.h"
#include "UI/MainMenu.h"
#include "UI/SingleplayerMenu.h"
#include "UI/SplitscreenMenu.h"
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
		lockMouseToWidget(mainMenu);
	}

	return mainMenu;
}

void UProjectRGameInstance::lockMouseToWidget(UMenu* menu)
{
	FInputModeUIOnly inputModeData;
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputModeData.SetWidgetToFocus(menu->TakeWidget());
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	controller->SetInputMode(inputModeData);
	controller->bShowMouseCursor = true;
}

UProjectRGameInstance::UProjectRGameInstance()
{
	numberOfPlayers = 1;
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
		lockMouseToWidget(singleplayerMenu);
	}
	return singleplayerMenu;
}

USplitscreenMenu* UProjectRGameInstance::loadSplitscreenMenu()
{
	USplitscreenMenu* splitscreenMenuInstance = Cast<USplitscreenMenu, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), USplitscreenMenu::StaticClass()));
	if (!splitscreenMenuInstance)
	{
		splitscreenMenu = CreateWidget<USplitscreenMenu>(GetWorld(), splitscreenMenuClass, FName("Splitscreen Menu"));
	}
	else
	{
		splitscreenMenu = splitscreenMenuInstance;
	}
	if (!splitscreenMenu->IsInViewport())
	{
		splitscreenMenu->AddToViewport();
		lockMouseToWidget(splitscreenMenu);
	}
	return splitscreenMenu;
}

bool UProjectRGameInstance::isMainMenuInViewport()
{
	if (!mainMenu)
	{
		return false;
	}
	return mainMenu->IsInViewport();
}

bool UProjectRGameInstance::isSingleplayerMenuInViewport()
{
	if (!singleplayerMenu)
	{
		return false;
	}
	return singleplayerMenu->IsInViewport();
}

void UProjectRGameInstance::expectedPlayers(int aQuantity)
{
	numberOfPlayers = aQuantity;
}

int UProjectRGameInstance::necessaryPlayers()
{
	return numberOfPlayers;
}
