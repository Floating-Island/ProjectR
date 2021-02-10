// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "SessionManager.generated.h"

class IOnlineSubsystem;
/**
 * 
 */
UCLASS()
class PROJECTR_API USessionManager : public UObject
{
	GENERATED_BODY()

	void checkSubsystemAndInterfaceConfigured();
	void prepareSubsystemAndInterface();
	void fetchAndConfigureSessionInterface();
	void fetchSessionInterface();
	void configureSessionInterfaceHandles();

public:
	USessionManager();

	bool createLANSession();

	FString lobbyName();

	bool destroyCurrentSession();

	bool searchLANSessions();

	TArray<FString> sessionSearchResults();
	
protected:
	IOnlineSubsystem* onlineSubsystem;
	IOnlineSessionPtr sessionInterface;

	FName lobbyMapName;

	bool hostSession(TSharedPtr<const FUniqueNetId> aUserID, FName aSessionName, bool isALANSession,
                                 bool hasPresence, int32 aPlayerCapacity);

	TSharedPtr<FOnlineSessionSettings> retrieveConfiguredSessionSettings(bool isALANSession, bool hasPresence, int32 aPlayerCapacity);


	TSharedPtr<class FOnlineSessionSearch> sessionSearch;
	int maximumNumberOfSearches;
	int maximumPingSizeAllowed;
	void configureSessionSearch(bool isALANSession, bool hasPresence);
	
	bool searchSessions(TSharedPtr<const FUniqueNetId> aUserID, bool isALANSession,
                                 bool hasPresence);
	
	//handles
	FDelegateHandle sessionCreationCompletedDelegateHandle;
	FDelegateHandle sessionStartCompletedDelegateHandle;
	FDelegateHandle sessionFindCompletedDelegateHandle;

	//delegates
	FOnCreateSessionCompleteDelegate sessionCreationCompletedDelegate;
	FOnStartSessionCompleteDelegate sessionStartCompletedDelegate;
	FOnFindSessionsCompleteDelegate sessionFindCompletedDelegate;

	//events
	void sessionCreatedEvent(FName sessionName, bool bWasSuccessful);
	void sessionStartedEvent(FName sessionName, bool bWasSuccessful);
	void sessionsSearchedEvent(bool bWasSuccessful);
	
	
};
