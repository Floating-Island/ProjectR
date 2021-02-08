// Fill out your copyright notice in the Description page of Project Settings.


#include "Session/SessionManager.h"
#include "OnlineSubsystem.h"


USessionManager::USessionManager()
{
	onlineSubsystem = IOnlineSubsystem::Get();
	makeSession();
}

void USessionManager::makeSession()
{
	if(onlineSubsystem)
	{
		sessionInterface = onlineSubsystem->GetSessionInterface();
	}
}