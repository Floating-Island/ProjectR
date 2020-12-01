// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SoloRaceMenu.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class PROJECTR_API USoloRaceMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
		void play();

	UFUNCTION()
		void goBack();

	UPROPERTY(meta = (BindWidget))
		UButton* playButton;

	UPROPERTY(meta = (BindWidget))
		UButton* goBackButton;

	UPROPERTY(EditAnywhere, Category="Race Map")
		FName raceLevel;

public:
	virtual bool Initialize() override;

	FVector2D playButtonAbsoluteCenterPosition();

	FVector2D goBackButtonAbsoluteCenterPosition();
};
