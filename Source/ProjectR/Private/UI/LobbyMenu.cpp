// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LobbyMenu.h"

#include "GameFramework/GameStateBase.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "UI/MapSelectorWidget.h"
#include "GameState/LobbyGameState.h"

void ULobbyMenu::returnToMainMenu()
{
	GetGameInstance()->ReturnToMainMenu();
}

void ULobbyMenu::startRace()
{
	if(localOwnerHasAuthority())
	{
		focusPlayersOnGame();
		FString mapSelected = mapListing->selectedMap();
		FString travelURL = mapSelected + FString("?listen") + FString("?numControllers=") + FString::FromInt(GetWorld()->GetNumPlayerControllers());
		GetWorld()->ServerTravel(travelURL, false, false);
	}
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

bool ULobbyMenu::localOwnerHasAuthority()
{
	ULocalPlayer* localPlayer = GetOwningLocalPlayer();
	return localPlayer?  localPlayer->PlayerController->HasAuthority() : true;
}

void ULobbyMenu::subscribeGameStateToMapUpdateEvent()
{
	ALobbyGameState* gameState = Cast<ALobbyGameState, AGameStateBase>(GetWorld()->GetGameState());
	if(gameState)
	{
		if(localOwnerHasAuthority())
		{
			mapListing->subscribeToMapUpdate(gameState);
			mapListing->subscribeToMapUpdate(this);
		}
		else
		{
			gameState->subscribeToLobbyMapUpdate(this);
		}
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ULobbyMenu::subscribeGameStateToMapUpdateEvent);
	}
}

void ULobbyMenu::updateSelectedMapText(FString aText)
{
	selectedMapText->SetText(FText::FromString(aText));	
}

bool ULobbyMenu::Initialize()
{
	bool initializeResult = Super::Initialize();

	bIsFocusable = true;

	bool doesntHaveAuthority = localOwnerHasAuthority() == false;
	
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
		if(doesntHaveAuthority)
		{
			mapListing->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

	if(startRaceButton)
	{
		startRaceButton->OnClicked.AddDynamic(this, &ULobbyMenu::startRace);
		startRaceButton->OnPressed.AddDynamic(this, &ULobbyMenu::startRace);
		startRaceButton->IsFocusable = true;
		startRaceButton->SetClickMethod(EButtonClickMethod::MouseDown);

		if(doesntHaveAuthority)
		{
			startRaceButton->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	subscribeGameStateToMapUpdateEvent();
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

FString ULobbyMenu::selectedMap()
{
	return selectedMapText->GetText().ToString();
}
