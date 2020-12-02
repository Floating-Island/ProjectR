// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"
#include "Components/Button.h"
#include "GameInstance/ProjectRGameInstance.h"


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
		singleplayerButton->OnClicked.AddDynamic(this, &UMainMenu::bringSingleplayerMenu);
		singleplayerButton->OnPressed.AddDynamic(this, &UMainMenu::bringSingleplayerMenu);
		singleplayerButton->IsFocusable = true;
		singleplayerButton->SetClickMethod(EButtonClickMethod::MouseDown);
	}
	bIsFocusable = true;
	return initializeResult;
}

FVector2D UMainMenu::quitButtonAbsoluteCenterPosition()
{
	FVector2D buttonCenter = FVector2D(0.5f, 0.5f);
	return buttonAbsoluteCenterPosition(quitButton);
}

FVector2D UMainMenu::singleplayerButtonAbsoluteCenterPosition()
{
	return buttonAbsoluteCenterPosition(singleplayerButton);
}


void UMainMenu::quit()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

void UMainMenu::bringSingleplayerMenu()
{
	RemoveFromViewport();
	UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(GetWorld()->GetGameInstance());
	gameInstance->loadSingleplayerMenu();
}
