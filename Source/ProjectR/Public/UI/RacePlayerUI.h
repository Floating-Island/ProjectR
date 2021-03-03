// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "RacePlayerUI.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECTR_API URacePlayerUI : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
		UTextBlock* currentLapText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* totalLapsText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* currentPositionText;

	void changeIntegerTextOf(UTextBlock* aTextBlock, int aNewValue);

public:
	virtual bool Initialize() override;

	UFUNCTION()
		void updateLapTo(int aNewLap);
	
	UFUNCTION()
		void updatePositionTo(int aNewPosition);

	UFUNCTION()
		void modifyTotalLapsTo(int aNewTotalLapsValue);
	
	void setTotalLapsTo(int aDesiredValue);
	
	int currentLap();
	int totalLaps();
	int currentPosition();
};
