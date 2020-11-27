// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"
#include "Components/Button.h"



bool UMainMenu::Initialize()
{
	bool initializeResult = Super::Initialize();
	if (quitButton)
	{
		quitButton->OnClicked.AddDynamic(this, &UMainMenu::quit);
	}
	bIsFocusable = true;
	return initializeResult;
}

FVector2D UMainMenu::quitButtonCenterPosition()
{
    FVector2D buttonCenter = quitButton->GetTickSpaceGeometry().GetAbsoluteSize() / 2.0f;
	return quitButton->GetTickSpaceGeometry().GetAbsolutePosition() + buttonCenter;
}


void UMainMenu::quit()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
