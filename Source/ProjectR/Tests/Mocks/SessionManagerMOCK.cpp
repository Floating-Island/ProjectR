// Fill out your copyright notice in the Description page of Project Settings.


#include "SessionManagerMOCK.h"

#include "OnlineSessionSettings.h"

IOnlineSubsystem* USessionManagerMOCK::retrieveSessionSubsystem()
{
	return onlineSubsystem;
}

IOnlineSessionPtr USessionManagerMOCK::retrieveSessionInterface()
{
	return sessionInterface;
}

void USessionManagerMOCK::setArbitrarySessionSearchResults(
	TSharedPtr<FOnlineSessionSearch> anArbitrarySessionSearch)
{
	sessionSearch = anArbitrarySessionSearch;
}

void USessionManagerMOCK::configureSubsystemAndInterface()
{
	checkSubsystemAndInterfaceConfigured();
}

bool USessionManagerMOCK::isBoundToFOnCreateSessionCompleteDelegate()
{
	return sessionCreationCompletedDelegate.IsBoundToObject(this);
}

bool USessionManagerMOCK::isBoundToFOnStartSessionCompleteDelegate()
{
	return sessionStartCompletedDelegate.IsBoundToObject(this);
}

bool USessionManagerMOCK::isBoundToFOnFindSessionsCompleteDelegate()
{
	return sessionFindCompletedDelegate.IsBoundToObject(this);
}

bool USessionManagerMOCK::isBoundToFOnJoinSessionCompleteDelegate()
{
	return sessionFindCompletedDelegate.IsBoundToObject(this);
}
