// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UPauseMenu::returnToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), mainMenuLevel);
}

FVector2D UPauseMenu::returnButtonAbsoluteCenterPosition()
{
	return buttonAbsoluteCenterPosition(returnButton);
}

bool UPauseMenu::Initialize()
{
	bool initializeResult = Super::Initialize();

	if(returnButton)
	{
		returnButton->OnClicked.AddDynamic(this, &UPauseMenu::returnToMainMenu);
		returnButton->OnPressed.AddDynamic(this, &UPauseMenu::returnToMainMenu);
		bIsFocusable = true;
	}
	bIsFocusable = true;

	return initializeResult;
}
