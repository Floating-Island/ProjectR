// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StringHolderButton.h"
#include "UI/StringButtonScrollBox.h"

bool UStringHolderButton::Initialize()
{
	bool initializeResult = Super::Initialize();
	bIsFocusable = true;
	if(textButton)
	{
		textButton->OnClicked.AddDynamic(this, &UStringHolderButton::buttonClickedEvent);
		textButton->OnPressed.AddDynamic(this, &UStringHolderButton::buttonClickedEvent);
		textButton->IsFocusable = true;
		textButton->SetClickMethod(EButtonClickMethod::MouseDown);
	}
	
	return initializeResult;
}

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

FVector2D UStringHolderButton::buttonCoordinates()
{
	FVector2D buttonCenter = FVector2D(0.5f, 0.5f);
	return textButton->GetTickSpaceGeometry().GetAbsolutePositionAtCoordinates(buttonCenter);
}

void UStringHolderButton::buttonClickedEvent()
{
	UStringButtonScrollBox* expectedParent = Cast<UStringButtonScrollBox, UObject>(GetTypedOuter(UStringButtonScrollBox::StaticClass()));
	if(expectedParent)
	{
		expectedParent->childClicked(this);
	}
}
