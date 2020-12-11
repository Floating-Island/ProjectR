// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LocalMultiplayerMenu.h"

#include "Components/Button.h"
#include "GameInstance/ProjectRGameInstance.h"


void ULocalMultiplayerMenu::goBack()
{
	RemoveFromViewport();
	UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(GetWorld()->GetGameInstance());
	gameInstance->loadMainMenu();
}

bool ULocalMultiplayerMenu::Initialize()
{
	bool initializeResult = Super::Initialize();

	if (goBackButton)
	{
		goBackButton->OnClicked.AddDynamic(this, &ULocalMultiplayerMenu::goBack);
		goBackButton->OnPressed.AddDynamic(this, &ULocalMultiplayerMenu::goBack);
		goBackButton->IsFocusable = true;
		goBackButton->SetClickMethod(EButtonClickMethod::MouseDown);
	}
	bIsFocusable = true;
	return initializeResult;
}

FVector2D ULocalMultiplayerMenu::goBackButtonAbsoluteCenterPosition()
{
	return buttonAbsoluteCenterPosition(goBackButton);
}
