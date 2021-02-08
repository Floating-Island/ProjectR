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

	void makeSession();
	
public:
	USessionManager();

	bool createLANSession();
	
protected:
	IOnlineSubsystem* onlineSubsystem;
	IOnlineSessionPtr sessionInterface;

	FName lobbyMapName;
	
	bool hostSession(TSharedPtr<const FUniqueNetId> aUserID, FName aSessionName, bool isALANSession,
                                 bool hasPresence, int32 aPlayerCapacity);

	TSharedPtr<FOnlineSessionSettings> retrieveConfiguredSessionSettings(bool isALANSession, bool hasPresence, int32 aPlayerCapacity);
};
