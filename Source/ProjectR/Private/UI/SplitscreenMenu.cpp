// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SplitscreenMenu.h"

#include "Components/Button.h"
#include "GameInstance/ProjectRGameInstance.h"


void USplitscreenMenu::goBack()
{
	RemoveFromViewport();
	UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(GetWorld()->GetGameInstance());
	gameInstance->loadMainMenu();
}

bool USplitscreenMenu::Initialize()
{
	bool initializeResult = Super::Initialize();

	if (goBackButton)
	{
		goBackButton->OnClicked.AddDynamic(this, &USplitscreenMenu::goBack);
		goBackButton->OnPressed.AddDynamic(this, &USplitscreenMenu::goBack);
		goBackButton->IsFocusable = true;
		goBackButton->SetClickMethod(EButtonClickMethod::MouseDown);
	}
	bIsFocusable = true;
	return initializeResult;
}

FVector2D USplitscreenMenu::goBackButtonAbsoluteCenterPosition()
{
	return buttonAbsoluteCenterPosition(goBackButton);
}
