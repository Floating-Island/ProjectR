// Fill out your copyright notice in the Description page of Project Settings.


#include "Session/SessionManager.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Kismet/GameplayStatics.h"


USessionManager::USessionManager()
{
	lobbyMapName = FName(FString("lobby"));
	sessionSearch = nullptr;
	maximumNumberOfSearches = 20;
	maximumPingSizeAllowed = 50;
}

void USessionManager::prepareSubsystemAndInterface()
{
	onlineSubsystem = IOnlineSubsystem::Get();
	fetchAndConfigureSessionInterface();
}

void USessionManager::fetchAndConfigureSessionInterface()
{
	fetchSessionInterface();
	configureSessionInterfaceHandles();
}

void USessionManager::fetchSessionInterface()
{
	if(onlineSubsystem)
	{
		sessionInterface = onlineSubsystem->GetSessionInterface();
	}
}

void USessionManager::configureSessionInterfaceHandles()
{
	sessionCreationCompletedDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &USessionManager::sessionCreatedEvent);
	sessionCreationCompletedDelegateHandle = sessionInterface->AddOnCreateSessionCompleteDelegate_Handle(sessionCreationCompletedDelegate);
	
	sessionStartCompletedDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &USessionManager::sessionStartedEvent);
	sessionStartCompletedDelegateHandle = sessionInterface->AddOnCreateSessionCompleteDelegate_Handle(sessionStartCompletedDelegate);

	sessionFindCompletedDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &USessionManager::sessionsSearchedEvent);
	sessionFindCompletedDelegateHandle = sessionInterface->AddOnFindSessionsCompleteDelegate_Handle(sessionFindCompletedDelegate);
}

void USessionManager::checkSubsystemAndInterfaceConfigured()
{
	if(onlineSubsystem == nullptr || sessionInterface == nullptr)
	{
		prepareSubsystemAndInterface();
	}
}

bool USessionManager::createLANSession()
{	
	return hostSession(GetWorld()->GetGameInstance()->GetPrimaryPlayerUniqueId(), GameSessionName, true, true, 8);
}

FString USessionManager::lobbyName()
{
	return lobbyMapName.ToString();
}

bool USessionManager::destroyCurrentSession()
{
	checkSubsystemAndInterfaceConfigured();
	return sessionInterface->DestroySession(GameSessionName);
}

bool USessionManager::searchLANSessions()
{
	return searchSessions(GetWorld()->GetGameInstance()->GetPrimaryPlayerUniqueId(), true, true);
}

bool USessionManager::hostSession(TSharedPtr<const FUniqueNetId> aUserID, FName aSessionName, bool isALANSession,
                                  bool hasPresence, int32 aPlayerCapacity)
{
	checkSubsystemAndInterfaceConfigured();
	if(sessionInterface.IsValid() && aUserID.IsValid())
	{
		TSharedPtr<FOnlineSessionSettings> sessionSettings = retrieveConfiguredSessionSettings(isALANSession, hasPresence, aPlayerCapacity);

		sessionSettings->Set(SETTING_MAPNAME, lobbyMapName.ToString(), EOnlineDataAdvertisementType::ViaOnlineService);
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

void USessionManager::configureSessionSearch(bool isALANSession, bool hasPresence)
{
	sessionSearch = MakeShared<FOnlineSessionSearch>();

	sessionSearch->bIsLanQuery = isALANSession;
	sessionSearch->MaxSearchResults = maximumNumberOfSearches;
	sessionSearch->PingBucketSize = maximumPingSizeAllowed;

	if(hasPresence)
	{
		sessionSearch->QuerySettings.Set(SEARCH_PRESENCE, hasPresence, EOnlineComparisonOp::Equals);
	}
}

bool USessionManager::searchSessions(TSharedPtr<const FUniqueNetId> aUserID, bool isALANSession, bool hasPresence)
{
	checkSubsystemAndInterfaceConfigured();
	if (sessionInterface.IsValid() && aUserID.IsValid())
	{
		configureSessionSearch(isALANSession, hasPresence);
		TSharedRef<FOnlineSessionSearch> searchSettings = sessionSearch.ToSharedRef();

		return sessionInterface->FindSessions(*aUserID, searchSettings);
	}
	return false;
}

TSet<FOnlineSessionSearchResult> USessionManager::sessionSearchResults()
{
	TSet<FOnlineSessionSearchResult> sessionsFound = TSet<FOnlineSessionSearchResult>();
	TSharedPtr<const FUniqueNetId> ownUserID = GetWorld()->GetGameInstance()->GetPrimaryPlayerUniqueId();
	
	for(const auto& session : sessionSearch->SearchResults)
	{
		if(session.Session.OwningUserId != ownUserID)
		{
			sessionsFound.Add(session);
		}
	}
	return sessionsFound;
}

void USessionManager::sessionCreatedEvent(FName sessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Log, TEXT("Session %s creation was %s."), (*sessionName.ToString()), (bWasSuccessful)? (*FString("Successful")):(*FString("Unsuccessful")));

	if (sessionInterface.IsValid() && bWasSuccessful)
	{
		sessionInterface->StartSession(sessionName);
	}
}

void USessionManager::sessionStartedEvent(FName sessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Log, TEXT("Session %s starting was %s."), (*sessionName.ToString()), (bWasSuccessful) ? (*FString("Successful")) : (*FString("Unsuccessful")));

	if (sessionInterface.IsValid() && bWasSuccessful)
	{
		UGameplayStatics::OpenLevel(GetWorld(), lobbyMapName, true, "listen");
	}
}

void USessionManager::sessionsSearchedEvent(bool bWasSuccessful)
{
	UE_LOG(LogTemp, Log, TEXT("Session finding was %s."), (bWasSuccessful) ? (*FString("successful")) : (*FString("Unsuccessful")));

	if (sessionInterface.IsValid())
	{
		TArray<FOnlineSessionSearchResult> searchResults = sessionSearch->SearchResults;
		
		UE_LOG(LogTemp, Log, TEXT("Number of sessions found: %d."), searchResults.Num());

		UE_LOG(LogTemp, Log, TEXT("Sessions found:"));

		for (auto sessionFound : searchResults)
		{
			UE_LOG(LogTemp, Log, TEXT("%s"), *(sessionFound.Session.OwningUserName));
		}
	}
}
