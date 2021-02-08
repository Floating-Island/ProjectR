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

	void fetchAndConfigureSessionInterface();
	void fetchSessionInterface();
	void configureSessionInterfaceHandles();
	
public:
	USessionManager();

	bool createLANSession();

	void prepareSubsystemAndInterface();

	FString lobbyName();
	
protected:
	IOnlineSubsystem* onlineSubsystem;
	IOnlineSessionPtr sessionInterface;

	FName lobbyMapName;

	bool hostSession(TSharedPtr<const FUniqueNetId> aUserID, FName aSessionName, bool isALANSession,
                                 bool hasPresence, int32 aPlayerCapacity);

	TSharedPtr<FOnlineSessionSettings> retrieveConfiguredSessionSettings(bool isALANSession, bool hasPresence, int32 aPlayerCapacity);

	//delegates
	FOnCreateSessionCompleteDelegate sessionCreationCompletedDelegate;
	FOnStartSessionCompleteDelegate sessionStartCompletedDelegate;

	//handles
	FDelegateHandle sessionCreationCompletedDelegateHandle;
	FDelegateHandle sessionStartCompletedDelegateHandle;

	//events
	void sessionCreatedEvent(FName sessionName, bool bWasSuccessful);
	void sessionStartedEvent(FName sessionName, bool bWasSuccessful);
	
	
};
