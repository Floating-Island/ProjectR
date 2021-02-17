// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "StringHolderButton.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTR_API UStringHolderButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void store(FString aString);
	FString storedString();

protected:

	UPROPERTY(meta = (BindWidget))
		UButton* textButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* textHolder;
};