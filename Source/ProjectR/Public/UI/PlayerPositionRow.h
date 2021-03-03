// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerPositionRow.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECTR_API UPlayerPositionRow : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
		UTextBlock* playerNameText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* positionText;
	

public:

	void updateInfoWith(FString aPlayerName, FString aPosition);
};
