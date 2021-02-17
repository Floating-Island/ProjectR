// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StringButtonScrollBox.h"

#include "UI/StringHolderButton.h"


void UStringButtonScrollBox::populateBox(TArray<FString> aBunchOfStrings)
{
	if(scrollBoxWidget)
	{
		for(auto aString : aBunchOfStrings)
		{
			UStringHolderButton* stringButtonWidget = Cast<UStringHolderButton, UUserWidget>(CreateWidget(this, stringHolderButtonClass));
			if(stringButtonWidget)
			{
				stringButtonWidget->store(aString);
				scrollBoxWidget->AddChild(stringButtonWidget);
			}
		}
	}
}

int UStringButtonScrollBox::stringButtonsQuantity()
{
	return scrollBoxWidget->GetChildrenCount();
}
