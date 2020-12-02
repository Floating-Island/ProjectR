// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"
#include "Components/Button.h"



bool UMainMenu::Initialize()
{
	bool initializeResult = Super::Initialize();
	if (quitButton)
	{
		quitButton->OnClicked.AddDynamic(this, &UMainMenu::quit);
		quitButton->OnPressed.AddDynamic(this, &UMainMenu::quit);
		quitButton->IsFocusable = true;
		quitButton->SetClickMethod(EButtonClickMethod::MouseDown);
	}
	if (singleplayerButton)
	{
		singleplayerButton->OnClicked.AddDynamic(this, &UMainMenu::bringSoloRaceMenu);
		singleplayerButton->OnPressed.AddDynamic(this, &UMainMenu::bringSoloRaceMenu);
		singleplayerButton->IsFocusable = true;
		singleplayerButton->SetClickMethod(EButtonClickMethod::MouseDown);
	}
	bIsFocusable = true;
	return initializeResult;
}

FVector2D UMainMenu::quitButtonAbsouluteCenterPosition()
{
	FVector2D buttonCenter = FVector2D(0.5f, 0.5f);
	return quitButton->GetTickSpaceGeometry().GetAbsolutePositionAtCoordinates(buttonCenter);
}

FVector2D UMainMenu::singleplayerButtonAbsoluteCenterPosition()
{
	FVector2D buttonCenter = FVector2D(0.5f, 0.5f);
	return singleplayerButton->GetTickSpaceGeometry().GetAbsolutePositionAtCoordinates(buttonCenter);
}


void UMainMenu::quit()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

void UMainMenu::bringSoloRaceMenu()
{
	RemoveFromViewport();
}
