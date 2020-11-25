// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"
#include "Components/Button.h"
#include "Blueprint/WidgetTree.h"

void UMainMenu::quit()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

bool UMainMenu::Initialize()
{
	bool initializeResult = Super::Initialize();
	quitButton = CreateWidget<UButton>(this, UButton::StaticClass(), FName("Quit Button"));
	quitButton->OnClicked.AddDynamic(this, &UMainMenu::quit);

	return initializeResult;
}
