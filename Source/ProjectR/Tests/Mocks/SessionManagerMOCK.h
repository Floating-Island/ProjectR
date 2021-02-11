// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Session/SessionManager.h"
#include "SessionManagerMOCK.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API USessionManagerMOCK : public USessionManager
{
	GENERATED_BODY()


public:

	IOnlineSubsystem* retrieveSessionSubsystem();
	IOnlineSessionPtr retrieveSessionInterface();

	void setArbitrarySessionSearchResults(TArray<FOnlineSessionSearchResult> anArbitrarySearchResultsArray);
};
