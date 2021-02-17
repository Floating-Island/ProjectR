// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StringHolderButton.h"

void UStringHolderButton::store(FString aString)
{
	text = aString;
}

FString UStringHolderButton::storedString()
{
	return text;
}
