// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AnnouncerUI.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECTR_API UAnnouncerUI : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
		UTextBlock* displayText;
	
public:
	virtual bool Initialize() override;

	UFUNCTION()
		void modifyWith(FString aDisplayText);
	
	FString assignedText();
};
