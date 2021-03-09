// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LocalMultiplayerMenu.h"


#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "GameInstance/ProjectRGameInstance.h"
#include "Components/ComboBoxString.h"
#include "UI/MapSelectorWidget.h"


void ULocalMultiplayerMenu::goBack()
{
	RemoveFromViewport();
	UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(GetWorld()->GetGameInstance());
	gameInstance->loadMainMenu();
}

void ULocalMultiplayerMenu::play()
{
	UProjectRGameInstance* gameInstance = Cast<UProjectRGameInstance, UGameInstance>(GetWorld()->GetGameInstance());
	gameInstance->expectedPlayers(selectedPlayerQuantity());
	focusOnGame();
	FString mapSelected = mapListing->selectedMap();
	if(mapSelected.IsEmpty())
	{
		return;
	}
	UGameplayStatics::OpenLevel(GetWorld(), FName(*mapSelected));
}

void ULocalMultiplayerMenu::focusOnGame()
{
	FInputModeGameOnly inputModeData;
	inputModeData.SetConsumeCaptureMouseDown(true);
	GetWorld()->GetFirstPlayerController()->SetInputMode(inputModeData);
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
	if (playButton)
	{
		playButton->OnClicked.AddDynamic(this, &ULocalMultiplayerMenu::play);
		playButton->OnPressed.AddDynamic(this, &ULocalMultiplayerMenu::play);
		playButton->IsFocusable = true;
		playButton->SetClickMethod(EButtonClickMethod::MouseDown);
	}
	bIsFocusable = true;
	return initializeResult;
}

FVector2D ULocalMultiplayerMenu::goBackButtonAbsoluteCenterPosition()
{
	return buttonAbsoluteCenterPosition(goBackButton);
}

FVector2D ULocalMultiplayerMenu::playButtonAbsoluteCenterPosition()
{
	return buttonAbsoluteCenterPosition(playButton);
}

int ULocalMultiplayerMenu::selectedPlayerQuantity()
{
	return FCString::Atoi(*playersQuantitySelection->GetSelectedOption());
}
