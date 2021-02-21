// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LanMultiplayerMenu.h"

#include "GameInstance/ProjectRGameInstance.h"
#include "Components/Button.h"
#include "UI/StringButtonScrollBox.h"
#include "TimerManager.h"

bool ULanMultiplayerMenu::Initialize()
{
	bool initializeResult = Super::Initialize();
	bIsFocusable = true;
	//gameInstance = Cast<UProjectRGameInstance, UGameInstance>(GetWorld()->GetGameInstance());
	
	if (goBackButton)
	{
		goBackButton->OnClicked.AddDynamic(this, &ULanMultiplayerMenu::goBack);
		goBackButton->OnPressed.AddDynamic(this, &ULanMultiplayerMenu::goBack);
		goBackButton->IsFocusable = true;
		goBackButton->SetClickMethod(EButtonClickMethod::MouseDown);
	}

	if (createSessionButton)
	{
		createSessionButton->OnClicked.AddDynamic(this, &ULanMultiplayerMenu::startLANSessionCreation);
		createSessionButton->OnPressed.AddDynamic(this, &ULanMultiplayerMenu::startLANSessionCreation);
		createSessionButton->IsFocusable = true;
		createSessionButton->SetClickMethod(EButtonClickMethod::MouseDown);
	}

	if (joinSessionButton)
	{
		joinSessionButton->OnClicked.AddDynamic(this, &ULanMultiplayerMenu::joinSelectedSession);
		joinSessionButton->OnPressed.AddDynamic(this, &ULanMultiplayerMenu::joinSelectedSession);
		joinSessionButton->IsFocusable = true;
		joinSessionButton->SetClickMethod(EButtonClickMethod::MouseDown);
		if(gameInstance)
		{
			//gameInstance->subscribeToSessionSearchedEvent<ULanMultiplayerMenu, &ULanMultiplayerMenu::sessionSearchCompletedAnd>(this);
			//gameInstance->startLANSessionsSearch();
		}
	}
	
	return initializeResult;
}

FVector2D ULanMultiplayerMenu::goBackButtonAbsoluteCenterPosition()
{
	return buttonAbsoluteCenterPosition(goBackButton);
}

FVector2D ULanMultiplayerMenu::createSessionButtonAbsoluteCenterPosition()
{
	return buttonAbsoluteCenterPosition(createSessionButton);
}

void ULanMultiplayerMenu::sessionSearchCompletedAnd(bool aSessionSearchWasSuccessful)
{
	/*UE_LOG(LogTemp, Log, TEXT("session search %s successful. Attempting to populate box and set timer..."), *FString(aSessionSearchWasSuccessful? "was" : "wasn't"));
	if(aSessionSearchWasSuccessful)
	{
		TArray<FString> foundSessionsID = gameInstance->sessionsFound();
		sessionListingBox->populateBoxWith(foundSessionsID);
		gameInstance->TimerManager->ClearTimer(retrySessionSearchTimer);
		if(IsInViewport())
		{
			gameInstance->TimerManager->SetTimer(retrySessionSearchTimer, gameInstance, &UProjectRGameInstance::startLANSessionsSearch, timeBetweenSearches);
		}
	}*/
}

void ULanMultiplayerMenu::goBack()
{
	//gameInstance->TimerManager->ClearTimer(retrySessionSearchTimer);
	RemoveFromViewport();
	Cast<UProjectRGameInstance, UGameInstance>(GetWorld()->GetGameInstance())->loadMainMenu();
}

void ULanMultiplayerMenu::startLANSessionCreation()
{
	//gameInstance->TimerManager->ClearTimer(retrySessionSearchTimer);
	//gameInstance->createLANSession();
}

void ULanMultiplayerMenu::joinSelectedSession()
{
	/*FString desiredSessionID = sessionListingBox->selectedString();*/

	/*gameInstance->joinSessionWith(desiredSessionID);*/
}
