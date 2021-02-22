// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LobbyMenu.h"
#include "Components/Button.h"

void ULobbyMenu::returnToMainMenu()
{
	GetGameInstance()->ReturnToMainMenu();
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

	return initializeResult;
}

FVector2D ULobbyMenu::returnButtonAbsoluteCenterPosition()
{
	return buttonAbsoluteCenterPosition(returnButton);
}
