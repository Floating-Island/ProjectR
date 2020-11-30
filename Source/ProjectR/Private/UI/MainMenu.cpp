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
		quitButton->SetClickMethod(EButtonClickMethod::MouseDown);
	}
	bIsFocusable = true;
	return initializeResult;
}

FVector2D UMainMenu::quitButtonLocalCenterPosition()
{
	FVector2D buttonCenter = FVector2D(0.5f, 0.5f);
	return quitButton->GetTickSpaceGeometry().GetLocalPositionAtCoordinates(buttonCenter);
}

FVector2D UMainMenu::quitButtonPixelCenterPosition()
{
	FVector2D viewportPosition = FVector2D();
	FVector2D pixelPosition = FVector2D();
	USlateBlueprintLibrary::LocalToViewport(GetWorld(), quitButton->GetTickSpaceGeometry(), FVector2D(0.5f, 0.5f), pixelPosition, viewportPosition);
	
	return pixelPosition;
}


void UMainMenu::quit()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
