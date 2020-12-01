// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SoloRaceMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USoloRaceMenu::play()
{
	RemoveFromViewport();
	UGameplayStatics::OpenLevel(GetWorld(), raceLevel);
}

void USoloRaceMenu::goBack()
{
	RemoveFromViewport();
}

bool USoloRaceMenu::Initialize()
{
	bool initializeResult = Super::Initialize();
	if (playButton)
	{
		playButton->OnClicked.AddDynamic(this, &USoloRaceMenu::play);
		playButton->OnPressed.AddDynamic(this, &USoloRaceMenu::play);
		playButton->IsFocusable = true;
		playButton->SetClickMethod(EButtonClickMethod::MouseDown);
	}
	if (goBackButton)
	{
		goBackButton->OnClicked.AddDynamic(this, &USoloRaceMenu::goBack);
		goBackButton->OnPressed.AddDynamic(this, &USoloRaceMenu::goBack);
		goBackButton->IsFocusable = true;
		goBackButton->SetClickMethod(EButtonClickMethod::MouseDown);
	}
	bIsFocusable = true;
	return initializeResult;
}

FVector2D USoloRaceMenu::playButtonAbsoluteCenterPosition()
{
	FVector2D buttonCenter = FVector2D(0.5f, 0.5f);
	return playButton->GetTickSpaceGeometry().GetAbsolutePositionAtCoordinates(buttonCenter);
}

FVector2D USoloRaceMenu::goBackButtonAbsoluteCenterPosition()
{
	FVector2D buttonCenter = FVector2D(0.5f, 0.5f);
	return goBackButton->GetTickSpaceGeometry().GetAbsolutePositionAtCoordinates(buttonCenter);
}
