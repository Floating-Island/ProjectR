// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AnnouncerUI.h"
#include "Components/TextBlock.h"

bool UAnnouncerUI::Initialize()
{
	bool initializeResult = Super::Initialize();

	if(displayText)
	{
		displayText->SetText(FText::FromString(FString(")-(")));
	}
	

	return initializeResult;
}

void UAnnouncerUI::modifyWith(FString aDisplayText)
{
	displayText->SetText(FText::FromString(aDisplayText));
}

FString UAnnouncerUI::assignedText()
{
	return displayText->GetText().ToString();
}
