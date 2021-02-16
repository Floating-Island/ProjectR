// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SessionHolderButton.h"

void USessionHolderButton::storeSessionResult(FOnlineSessionSearchResult aTestResult)
{
	sessionResult = aTestResult;
}

const FOnlineSessionSearchResult USessionHolderButton::sessionResultStored()
{
	return sessionResult;
}
