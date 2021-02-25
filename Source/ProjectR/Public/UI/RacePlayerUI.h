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

	void changeLapTextTo(int aNewLap);

public:
	virtual bool Initialize() override;
	UFUNCTION()
		void updateLapTo(int aNewLap);
	int currentLap();
};
