// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LanMultiplayerMenu.h"
#include "Components/Button.h"

bool ULanMultiplayerMenu::Initialize()
{
	bool initializeResult = Super::Initialize();
	bIsFocusable = true;

	if (goBackButton)
	{
		goBackButton->OnClicked.AddDynamic(this, &ULanMultiplayerMenu::goBack);
		goBackButton->OnPressed.AddDynamic(this, &ULanMultiplayerMenu::goBack);
		goBackButton->IsFocusable = true;
		goBackButton->SetClickMethod(EButtonClickMethod::MouseDown);
	}
	
	return initializeResult;
}

FVector2D ULanMultiplayerMenu::goBackButtonAbsoluteCenterPosition()
{
	buttonAbsoluteCenterPosition(goBackButton);
}

void ULanMultiplayerMenu::goBack()
{
	RemoveFromViewport();
}
