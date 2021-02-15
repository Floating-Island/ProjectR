// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/ProjectRGameInstance.h"
#include "UI/MainMenu.h"
#include "UI/SingleplayerMenu.h"
#include "UI/LocalMultiplayerMenu.h"
#include "UI/LanMultiplayerMenu.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Session/SessionManager.h"



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
	expectedPlayers(1);//obscure. Necessary to set the number of players when coming from a pause or going back to main menu from the local multiplayer menu.
	
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

ULocalMultiplayerMenu* UProjectRGameInstance::loadLocalMultiplayerMenu()
{
	ULocalMultiplayerMenu* localMultiplayerMenuInstance = Cast<ULocalMultiplayerMenu, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ULocalMultiplayerMenu::StaticClass()));
	if (!localMultiplayerMenuInstance)
	{
		localMultiplayerMenu = CreateWidget<ULocalMultiplayerMenu>(GetWorld(), localMultiplayerMenuClass, FName("Splitscreen Menu"));
	}
	else
	{
		localMultiplayerMenu = localMultiplayerMenuInstance;
	}
	if (!localMultiplayerMenu->IsInViewport())
	{
		localMultiplayerMenu->AddToViewport();
		lockMouseToWidget(localMultiplayerMenu);
	}
	return localMultiplayerMenu;
}

ULanMultiplayerMenu* UProjectRGameInstance::loadLANMUltiplayerMenu()
{
	lanMultiplayerMenu = CreateWidget<ULanMultiplayerMenu>(GetWorld(), lanMultiplayerMenuClass, FName("Lan Multiplayer Menu"));

	if (!lanMultiplayerMenu->IsInViewport())
	{
		lanMultiplayerMenu->AddToViewport();
	}
	return lanMultiplayerMenu;
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

bool UProjectRGameInstance::isLocalMultiplayerMenuInViewport()
{
	if (!localMultiplayerMenu)
	{
		return false;
	}
	return localMultiplayerMenu->IsInViewport();
}

void UProjectRGameInstance::expectedPlayers(int aQuantity)
{
	numberOfPlayers = aQuantity;
}

int UProjectRGameInstance::necessaryPlayers()
{
	return numberOfPlayers;
}

bool UProjectRGameInstance::sessionManagerIsConfigured()
{
	return sessionManager && sessionManager->isConfigured();
}

void UProjectRGameInstance::OnStart()
{
	Super::OnStart();
	sessionManager = NewObject<USessionManager>(this, USessionManager::StaticClass()->GetFName());
	sessionManager->checkSubsystemAndInterfaceConfigured();
}
