// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SessionHolderButton.h"
#include "OnlineSessionSettings.h"

void USessionHolderButton::storeSessionResult(const FOnlineSessionSearchResult& aTestResult)
{
	sessionResult = aTestResult;
}

const FOnlineSessionSearchResult& USessionHolderButton::sessionResultStored()
{
	return sessionResult;
}
