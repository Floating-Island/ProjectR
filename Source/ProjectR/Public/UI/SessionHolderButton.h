// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "OnlineSessionSettings.h"
#include "Components/Button.h"
#include "SessionHolderButton.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTR_API USessionHolderButton : public UUserWidget
{
	GENERATED_BODY()

 FOnlineSessionSearchResult sessionResult;
	
public:
	void storeSessionResult(FOnlineSessionSearchResult aTestResult);
	const FOnlineSessionSearchResult sessionResultStored();
};