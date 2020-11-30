// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"
#include "Components/Button.h"
#include "Blueprint/SlateBlueprintLibrary.h"



bool UMainMenu::Initialize()
{
	bool initializeResult = Super::Initialize();
	if (quitButton)
	{
		quitButton->OnClicked.AddDynamic(this, &UMainMenu::quit);
		quitButton->OnPressed.AddDynamic(this, &UMainMenu::quit);
		quitButton->IsFocusable = true;
	}
	bIsFocusable = true;
	return initializeResult;
}

void UMainMenu::quit()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
