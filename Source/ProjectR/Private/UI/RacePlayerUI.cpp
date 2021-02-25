// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RacePlayerUI.h"
#include "Components/TextBlock.h"

int URacePlayerUI::currentLap()
{
	return FCString::Atoi(*currentLapText->GetText().ToString());
}

int URacePlayerUI::currentPosition()
{
	return FCString::Atoi(*currentPositionText->GetText().ToString());
}

void URacePlayerUI::changeLapTextTo(int aNewLap)
{
	currentLapText->SetText(FText::FromString(FString::FromInt(aNewLap)));
}

void URacePlayerUI::changePositionTextTo(int aNewPosition)
{
	currentPositionText->SetText(FText::FromString(FString::FromInt(aNewPosition)));
}

bool URacePlayerUI::Initialize()
{
	bool initializeResult = Super::Initialize();
	if(currentLapText)
	{
		currentLapText->SetText(FText::FromString(FString("currentLap")));
	}

	if(currentPositionText)
	{
		currentPositionText->SetText(FText::FromString(FString("currentPosition")));
	}
	return initializeResult;
}

void URacePlayerUI::updateLapTo(int aNewLap)
{
	if(aNewLap > currentLap())
	{
		changeLapTextTo(aNewLap);
	}
}

void URacePlayerUI::updatePositionTo(int aNewPosition)
{
	changePositionTextTo(aNewPosition);
}
