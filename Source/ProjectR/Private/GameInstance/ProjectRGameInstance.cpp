// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/ProjectRGameInstance.h"
#include "UI/MainMenu.h"
#include "UI/SingleplayerMenu.h"
#include "UI/LocalMultiplayerMenu.h"
#include "UI/LanMultiplayerMenu.h"
#include "UI/LobbyMenu.h"
#include "Blueprint/UserWidget.h"
#include "Session/SessionManager.h"


void UProjectRGameInstance::lockMouseToWidget(UMenu* menu)
{
	FInputModeUIOnly inputModeData;
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputModeData.SetWidgetToFocus(menu->TakeWidget());
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	controller->SetInputMode(inputModeData);
	controller->bShowMouseCursor = true;
}

bool UProjectRGameInstance::menuIsInViewport(UMenu* aMenu)
{
	if (!aMenu)
	{
		return false;
	}
	return aMenu->IsInViewport();
}

void UProjectRGameInstance::keepFirstControllerOnly()
{
	APlayerController* firstController = GetWorld()->GetFirstPlayerController();

	TArray<APlayerController*> controllersToDestroy = TArray<APlayerController*>();
	for(auto controllerIterator = GetWorld()->GetControllerIterator(); controllerIterator; ++controllerIterator)
	{
		APlayerController* controller = Cast<APlayerController, AController>(controllerIterator->Get());
		if(controller && controller != firstController)
		{
			controllersToDestroy.Add(controller);
		}
	}

	for(auto& controller : controllersToDestroy)
	{
		UGameplayStatics::RemovePlayer(controller, true);
	}
}

UProjectRGameInstance::UProjectRGameInstance()
{
	numberOfPlayers = 1;
}

UMainMenu* UProjectRGameInstance::loadMainMenu()
{
	expectedPlayers(1);//obscure. Necessary to set the number of players when coming from a pause or going back to main menu from the local multiplayer menu.
	GetTimerManager().SetTimerForNextTick(this, &UProjectRGameInstance::keepFirstControllerOnly);
	mainMenu = loadMenuOfClass<UMainMenu>(mainMenuClass, FName("Main Menu"));
	return mainMenu;
}

USingleplayerMenu* UProjectRGameInstance::loadSingleplayerMenu()
{
	singleplayerMenu = loadMenuOfClass<USingleplayerMenu>(singleplayerMenuClass, FName("Singleplayer Menu"));
	return singleplayerMenu;
}

ULocalMultiplayerMenu* UProjectRGameInstance::loadLocalMultiplayerMenu()
{
	localMultiplayerMenu = loadMenuOfClass<ULocalMultiplayerMenu>(localMultiplayerMenuClass, FName("Splitscreen Menu"));
	return localMultiplayerMenu;
}

ULanMultiplayerMenu* UProjectRGameInstance::loadLANMUltiplayerMenu()
{
	lanMultiplayerMenu = loadMenuOfClass<ULanMultiplayerMenu>(lanMultiplayerMenuClass, FName("Lan Multiplayer Menu"));
	return lanMultiplayerMenu;
}

ULobbyMenu* UProjectRGameInstance::loadLobbyMenu()
{
	lobbyMenu = loadMenuOfClass<ULobbyMenu>(lobbyMenuClass, FName("Lobby Menu"));
	return lobbyMenu;
}

bool UProjectRGameInstance::isMainMenuInViewport()
{
	return menuIsInViewport(mainMenu);
}

bool UProjectRGameInstance::isSingleplayerMenuInViewport()
{
	return menuIsInViewport(singleplayerMenu);
}

bool UProjectRGameInstance::isLocalMultiplayerMenuInViewport()
{
	return menuIsInViewport(localMultiplayerMenu);
}

bool UProjectRGameInstance::isLanMultiplayerMenuInViewport()
{
	return menuIsInViewport(lanMultiplayerMenu);
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

void UProjectRGameInstance::createLANSession()
{
	sessionManager->createLANSession();
}

void UProjectRGameInstance::destroyOnlineSession()
{
	sessionManager->destroyCurrentSession();
}

TArray<FString> UProjectRGameInstance::sessionsFound()
{
	return sessionManager->sessionSearchResults();
}

void UProjectRGameInstance::startLANSessionsSearch()
{
	sessionManager->searchLANSessions();
}

void UProjectRGameInstance::joinSessionWith(FString aDesiredSessionID)
{
	sessionManager->joinSessionWith(aDesiredSessionID);
}

void UProjectRGameInstance::OnStart()
{
	Super::OnStart();
	sessionManager = NewObject<USessionManager>(this, USessionManager::StaticClass()->GetFName());
	sessionManager->checkSubsystemAndInterfaceConfigured();
}
