// Fill out your copyright notice in the Description page of Project Settings.


#include "Session/SessionManager.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"


USessionManager::USessionManager()
{
	onlineSubsystem = IOnlineSubsystem::Get();
	makeSession();
	lobbyMapName = FName(FString("lobby"));
}

bool USessionManager::createLANSession()
{
	return hostSession(GetWorld()->GetGameInstance()->GetPrimaryPlayerUniqueId(), GameSessionName, true, true, 8);
}

bool USessionManager::hostSession(TSharedPtr<const FUniqueNetId> aUserID, FName aSessionName, bool isALANSession,
	bool hasPresence, int32 aPlayerCapacity)
{
	if(sessionInterface.IsValid() && aUserID.IsValid())
	{
		TSharedPtr<FOnlineSessionSettings> sessionSettings = retrieveConfiguredSessionSettings(isALANSession, hasPresence, aPlayerCapacity);

		sessionSettings->Set(SETTING_MAPNAME, lobbyMapName.ToString(), EOnlineDataAdvertisementType::ViaOnlineService);

		return sessionInterface->CreateSession(*aUserID, aSessionName, *sessionSettings);
	}

	UE_LOG(LogTemp, Log, TEXT("Couldn't host session, no Online Subsystem present..."));
	return false;
}

TSharedPtr<FOnlineSessionSettings> USessionManager::retrieveConfiguredSessionSettings(bool isALANSession,
	bool hasPresence, int32 aPlayerCapacity)
{
	TSharedPtr<FOnlineSessionSettings> sessionSettings = MakeShared<FOnlineSessionSettings>();

	sessionSettings->bIsLANMatch = isALANSession;
	sessionSettings->bUsesPresence = hasPresence;
	sessionSettings->NumPublicConnections = aPlayerCapacity;
	sessionSettings->NumPrivateConnections = 0;
	sessionSettings->bAllowInvites = true;
	sessionSettings->bAllowJoinInProgress = true;
	sessionSettings->bShouldAdvertise = true;
	sessionSettings->bAllowJoinViaPresence = true;
	sessionSettings->bAllowJoinViaPresenceFriendsOnly = false;

	return sessionSettings;
}

void USessionManager::makeSession()
{
	if(onlineSubsystem)
	{
		sessionInterface = onlineSubsystem->GetSessionInterface();
	}
}
