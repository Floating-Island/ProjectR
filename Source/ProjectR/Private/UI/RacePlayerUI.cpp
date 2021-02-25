// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RacePlayerUI.h"
#include "Components/TextBlock.h"

int URacePlayerUI::currentLap()
{
	return FCString::Atoi(*currentLapText->GetText().ToString());
}

void URacePlayerUI::changeLapTextTo(int aNewLap)
{
	currentLapText->SetText(FText::FromString(FString::FromInt(aNewLap)));
}

bool URacePlayerUI::Initialize()
{
	bool initializeResult = Super::Initialize();
	if(currentLapText)
	{
		int firstLap = 1;
		changeLapTextTo(firstLap);
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
