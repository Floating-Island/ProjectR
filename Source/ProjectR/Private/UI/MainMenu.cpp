// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"
#include "Components/Button.h"



bool UMainMenu::Initialize()
{
	bool initializeResult = Super::Initialize();
	if(quitButton)
	{
		quitButton->OnClicked.AddDynamic(this, &UMainMenu::quit);
	}
	return initializeResult;
}

FVector2D UMainMenu::quitButtonPosition()
{
	return quitButton->GetCachedGeometry().GetAbsolutePosition();
}


void UMainMenu::quit()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
