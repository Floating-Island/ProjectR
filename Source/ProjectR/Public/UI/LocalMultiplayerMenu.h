// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu.h"
#include "LocalMultiplayerMenu.generated.h"

class UComboBoxString;
/**
 * 
 */
UCLASS()
class PROJECTR_API ULocalMultiplayerMenu : public UMenu
{
	GENERATED_BODY()

protected:
	void focusOnGame();
	
	UFUNCTION()
		void goBack();

	UFUNCTION()
		void play();

	UPROPERTY(meta = (BindWidget))
		UButton* goBackButton;

	UPROPERTY(meta = (BindWidget))
		UButton* playButton;

	UPROPERTY(meta = (BindWidget))
		UComboBoxString* playersQuantitySelection;

	UPROPERTY(EditAnywhere, Category="Race Map")
		FName raceLevel;

public:
	virtual bool Initialize() override;
	
	FVector2D goBackButtonAbsoluteCenterPosition();

	FVector2D playButtonAbsoluteCenterPosition();

	int selectedPlayerQuantity();
};
