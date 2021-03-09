// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SingleplayerMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "UI/MapSelectorWidget.h"


void USingleplayerMenu::play()
{
	focusOnGame();
	FString mapSelected = mapListing->selectedMap();
	if(mapSelected.IsEmpty())
	{
		return;
	}
	UGameplayStatics::OpenLevel(GetWorld(), FName(*mapSelected));
}

void USingleplayerMenu::focusOnGame()
{
	FInputModeGameOnly inputModeData;
	inputModeData.SetConsumeCaptureMouseDown(true);
	GetWorld()->GetFirstPlayerController()->SetInputMode(inputModeData);
}

void USingleplayerMenu::goBack()
{
	RemoveFromViewport();
	UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(GetWorld()->GetGameInstance());
	gameInstance->loadMainMenu();
}

bool USingleplayerMenu::Initialize()
{
	bool initializeResult = Super::Initialize();
	if (playButton)
	{
		playButton->OnClicked.AddDynamic(this, &USingleplayerMenu::play);
		playButton->OnPressed.AddDynamic(this, &USingleplayerMenu::play);
		playButton->IsFocusable = true;
		playButton->SetClickMethod(EButtonClickMethod::MouseDown);
	}
	if (goBackButton)
	{
		goBackButton->OnClicked.AddDynamic(this, &USingleplayerMenu::goBack);
		goBackButton->OnPressed.AddDynamic(this, &USingleplayerMenu::goBack);
		goBackButton->IsFocusable = true;
		goBackButton->SetClickMethod(EButtonClickMethod::MouseDown);
	}
	bIsFocusable = true;
	return initializeResult;
}

FVector2D USingleplayerMenu::playButtonAbsoluteCenterPosition()
{
	return buttonAbsoluteCenterPosition(playButton);
}

FVector2D USingleplayerMenu::goBackButtonAbsoluteCenterPosition()
{
	return buttonAbsoluteCenterPosition(goBackButton);
}
