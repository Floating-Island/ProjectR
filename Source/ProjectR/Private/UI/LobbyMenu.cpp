// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LobbyMenu.h"
#include "Components/Button.h"
#include "UI/MapSelectorWidget.h"

void ULobbyMenu::returnToMainMenu()
{
	GetGameInstance()->ReturnToMainMenu();
}

void ULobbyMenu::startRace()
{
	FString mapSelected = mapListing->selectedMap();
	GetWorld()->ServerTravel(mapSelected, false, true);
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

FVector2D ULobbyMenu::returnButtonAbsoluteCenterPosition()
{
	return buttonAbsoluteCenterPosition(returnButton);
}

FVector2D ULobbyMenu::startRaceButtonAbsoluteCenterPosition()
{
	return buttonAbsoluteCenterPosition(startRaceButton);
}
