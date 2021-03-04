// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../PlayerState/RacePlayerState.h"
#include "Blueprint/UserWidget.h"
#include "RaceResultsUI.generated.h"

class UPlayerPositionRow;
class UVerticalBox;
/**
 * 
 */
UCLASS()
class PROJECTR_API URaceResultsUI : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
		UVerticalBox* infoBox;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
		TSubclassOf<UPlayerPositionRow> playerPositionRowClass;
	
	void repopulateInfoBox();
	void fillInfoBoxWith(const TTuple<FString, int>& aPlayerNameAndPositionTuple);
	
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	int rowsQuantity();
	
};
