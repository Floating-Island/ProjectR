// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RacePlayerUI.h"
#include "Components/TextBlock.h"

int URacePlayerUI::currentLap()
{
	return FCString::Atoi(*currentLapText->GetText().ToString());
}

int URacePlayerUI::totalLaps()
{
	return FCString::Atoi(*totalLapsText->GetText().ToString());
}

int URacePlayerUI::currentPosition()
{
	return FCString::Atoi(*currentPositionText->GetText().ToString());
}

void URacePlayerUI::setTotalLapsTo(int aDesiredValue)
{
	if(totalLapsText->GetText().ToString().Contains("(Total Laps)"))
	{
		changeIntegerTextOf(totalLapsText, aDesiredValue);
	}
}

void URacePlayerUI::changeIntegerTextOf(UTextBlock* aTextBlock, int aNewValue)
{
	aTextBlock->SetText(FText::FromString(FString::FromInt(aNewValue)));
}

bool URacePlayerUI::Initialize()
{
	bool initializeResult = Super::Initialize();
	if(currentLapText)
	{
		currentLapText->SetText(FText::FromString(FString("(Current Lap)")));
	}

	if(totalLapsText)
	{
		totalLapsText->SetText(FText::FromString(FString("(Total Laps)")));
	}

	if(currentPositionText)
	{
		currentPositionText->SetText(FText::FromString(FString("(Current Position)")));
	}
	return initializeResult;
}

void URacePlayerUI::updateLapTo(int aNewLap)
{
	changeIntegerTextOf(currentLapText, aNewLap);
}

void URacePlayerUI::updatePositionTo(int aNewPosition)
{
	changeIntegerTextOf(currentPositionText, aNewPosition);
}

void URacePlayerUI::modifyTotalLapsTo(int aNewTotalLapsValue)
{
	changeIntegerTextOf(totalLapsText, aNewTotalLapsValue);
}
