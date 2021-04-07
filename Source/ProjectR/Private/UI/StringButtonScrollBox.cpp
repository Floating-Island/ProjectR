// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StringButtonScrollBox.h"



#include "UI/LobbyMenu.h"
#include "GameState/LobbyGameState.h"
#include "UI/StringHolderButton.h"


void UStringButtonScrollBox::childClicked(UStringHolderButton* aChild)
{
	if(selectedChild != aChild && aChild->GetTypedOuter(StaticClass()))
	{
		selectedChild = aChild;
		fireSelectedStringUpdateEvent();
	}
}

void UStringButtonScrollBox::subscribeToSelectedStringUpdate(ALobbyGameState* aGameState)
{
	mapUpdateEvent.AddUniqueDynamic(aGameState, &ALobbyGameState::updateSelectedMap);
	fireSelectedStringUpdateEvent();
}

void UStringButtonScrollBox::subscribeToSelectedStringUpdate(ULobbyMenu* aLobbyMenu)
{
	mapUpdateEvent.AddUniqueDynamic(aLobbyMenu, &ULobbyMenu::updateSelectedMapText);
	fireSelectedStringUpdateEvent();
}

void UStringButtonScrollBox::fireSelectedStringUpdateEvent()
{
	mapUpdateEvent.Broadcast(selectedString());
}

bool UStringButtonScrollBox::Initialize()
{
	bool initializeResult = Super::Initialize();
	selectedChild = nullptr;
	bIsFocusable = true;
	return initializeResult;
}

void UStringButtonScrollBox::populateBoxWith(TArray<FString> aBunchOfStrings)
{
	selectedChild = nullptr;
	scrollBoxWidget->ClearChildren();
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

int UStringButtonScrollBox::stringButtonsQuantity()
{
	return scrollBoxWidget->GetChildrenCount();
}

FString UStringButtonScrollBox::selectedString()
{
	return selectedChild? selectedChild->storedString() : FString();
}
