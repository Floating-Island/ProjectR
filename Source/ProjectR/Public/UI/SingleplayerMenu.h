// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu.h"
#include "SingleplayerMenu.generated.h"

class UMapSelectorWidget;
class UButton;
/**
 * 
 */
UCLASS()
class PROJECTR_API USingleplayerMenu : public UMenu
{
	GENERATED_BODY()

protected:
	void focusOnGame();
	UFUNCTION()
		void play();

	UFUNCTION()
		void goBack();

	UPROPERTY(meta = (BindWidget))
		UButton* playButton;

	UPROPERTY(meta = (BindWidget))
		UButton* goBackButton;

	UPROPERTY(meta = (BindWidget))
		UMapSelectorWidget* mapListing;

public:
	virtual bool Initialize() override;

	FVector2D playButtonAbsoluteCenterPosition();

	FVector2D goBackButtonAbsoluteCenterPosition();
};
