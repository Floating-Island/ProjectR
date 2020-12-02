// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu.h"
#include "Components/Button.h"

FVector2D UMenu::buttonAbsoluteCenterPosition(UButton *aButton)
{
	FVector2D buttonCenter = FVector2D(0.5f, 0.5f);
	return aButton->GetTickSpaceGeometry().GetAbsolutePositionAtCoordinates(buttonCenter);
}

bool UMenu::Initialize()
{
	return Super::Initialize();
}
