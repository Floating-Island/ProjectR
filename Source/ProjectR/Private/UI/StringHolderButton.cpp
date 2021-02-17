// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StringHolderButton.h"

void UStringHolderButton::store(FString aString)
{
	if(textHolder)
	{
		textHolder->SetText(FText::FromString(aString));
	}
}

FString UStringHolderButton::storedString()
{
	return textHolder->GetText().ToString();
}
