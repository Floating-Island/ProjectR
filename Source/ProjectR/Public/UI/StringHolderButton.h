// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "OnlineSessionSettings.h"
#include "Components/Button.h"
#include "StringHolderButton.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTR_API UStringHolderButton : public UUserWidget
{
	GENERATED_BODY()

 FString text;
	
public:
	void store(FString aString);
	FString storedString();
};