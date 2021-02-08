// Fill out your copyright notice in the Description page of Project Settings.


#include "Session/SessionManager.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"


USessionManager::USessionManager()
{
	lobbyMapName = FString("lobby");
}

bool USessionManager::createLANSession()
{
	return hostSession(GetWorld()->GetGameInstance()->GetPrimaryPlayerUniqueId(), GameSessionName, true, true, 8);
}

void USessionManager::prepareSubsystemAndInterface()
{
	onlineSubsystem = IOnlineSubsystem::Get();
	fetchSessionInterface();
}

bool USessionManager::hostSession(TSharedPtr<const FUniqueNetId> aUserID, FName aSessionName, bool isALANSession,
                                  bool hasPresence, int32 aPlayerCapacity)
{
	if(sessionInterface.IsValid() && aUserID.IsValid())
	{
		TSharedPtr<FOnlineSessionSettings> sessionSettings = retrieveConfiguredSessionSettings(isALANSession, hasPresence, aPlayerCapacity);

		sessionSettings->Set(SETTING_MAPNAME, lobbyMapName, EOnlineDataAdvertisementType::ViaOnlineService);
		return sessionInterface->CreateSession(*aUserID, aSessionName, *sessionSettings);
	}
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

void USessionManager::fetchSessionInterface()
{
	if(onlineSubsystem)
	{
		sessionInterface = onlineSubsystem->GetSessionInterface();
	}
}
