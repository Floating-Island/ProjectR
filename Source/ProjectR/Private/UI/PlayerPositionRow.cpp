// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerPositionRow.h"
#include "Components/TextBlock.h"

void UPlayerPositionRow::updateInfoWith(FString aPlayerName, FString aPosition)
{
	playerNameText->SetText(FText::FromString(aPlayerName));
	positionText->SetText(FText::FromString(aPosition));
}

FString UPlayerPositionRow::playerName()
{
	return playerNameText->GetText().ToString();
}

FString UPlayerPositionRow::position()
{
	return positionText->GetText().ToString();
}
