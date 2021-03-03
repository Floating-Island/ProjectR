// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LobbyMenu.h"

#include "GameFramework/GameStateBase.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "UI/MapSelectorWidget.h"

void ULobbyMenu::returnToMainMenu()
{
	GetGameInstance()->ReturnToMainMenu();
}

void ULobbyMenu::startRace()
{
	focusPlayersOnGame();
	FString mapSelected = mapListing->selectedMap();
	FString travelURL = mapSelected + FString("?listen") + FString("?numControllers=") + FString::FromInt(GetWorld()->GetNumPlayerControllers());
	GetWorld()->ServerTravel(travelURL, false, false);
}

void ULobbyMenu::focusPlayersOnGame()
{
	FInputModeGameOnly inputModeData;
	inputModeData.SetConsumeCaptureMouseDown(true);
	for (auto iterator = GetWorld()->GetPlayerControllerIterator(); iterator; ++iterator)//check if it works. Check that clients are able to move. After dealing with postlogin in gamemode...
	{
		APlayerController* controller = iterator->Get();
		controller->SetInputMode(inputModeData);
	}
}

void ULobbyMenu::updatePlayersInLobby()
{
	if(playersInLobbyText)
	{
		int playersInGameState = GetWorld()->GetGameState()->PlayerArray.Num();
		int playersInLobbyNumber = FCString::Atoi(*playersInLobbyText->GetText().ToString());
		
		if(playersInGameState == playersInLobbyNumber)
		{
			return;
		}
		playersInLobbyText->SetText(FText::FromString(FString::FromInt(playersInGameState)));
	}
}

bool ULobbyMenu::Initialize()
{
	bool initializeResult = Super::Initialize();

	bIsFocusable = true;

	if(returnButton)
	{
		returnButton->OnClicked.AddDynamic(this, &ULobbyMenu::returnToMainMenu);
		returnButton->OnPressed.AddDynamic(this, &ULobbyMenu::returnToMainMenu);
		returnButton->IsFocusable = true;
		returnButton->SetClickMethod(EButtonClickMethod::MouseDown);
	}

	if(mapListing)
	{
		mapListing->bIsFocusable = true;
	}

	if(startRaceButton)
	{
		startRaceButton->OnClicked.AddDynamic(this, &ULobbyMenu::startRace);
		startRaceButton->OnPressed.AddDynamic(this, &ULobbyMenu::startRace);
		startRaceButton->IsFocusable = true;
		startRaceButton->SetClickMethod(EButtonClickMethod::MouseDown);
	}

	return initializeResult;
}

void ULobbyMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	updatePlayersInLobby();
}

FVector2D ULobbyMenu::returnButtonAbsoluteCenterPosition()
{
	return buttonAbsoluteCenterPosition(returnButton);
}

FVector2D ULobbyMenu::startRaceButtonAbsoluteCenterPosition()
{
	return buttonAbsoluteCenterPosition(startRaceButton);
}

int ULobbyMenu::connectedPlayers()
{
	if(playersInLobbyText)
	{
		return FCString::Atoi(*playersInLobbyText->GetText().ToString());
	}
	return -1;
}
