// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu.h"
#include "MainMenu.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class PROJECTR_API UMainMenu : public UMenu
{
	GENERATED_BODY()

protected:
	UFUNCTION()
		void quit();

	UFUNCTION()
		void bringSingleplayerMenu();
	
	UFUNCTION()
		void bringLocalMultiplayerMenu();

	UFUNCTION()
		void bringLanMultiplayerMenu();

	UPROPERTY(meta = (BindWidget))
		UButton* quitButton;

	UPROPERTY(meta = (BindWidget))
		UButton* singleplayerButton;
	
	UPROPERTY(meta = (BindWidget))
		UButton* localMultiplayerButton;

	UPROPERTY(meta = (BindWidget))
		UButton* lanMultiplayerButton;

public:
	virtual bool Initialize() override;

	FVector2D quitButtonAbsoluteCenterPosition();

	FVector2D singleplayerButtonAbsoluteCenterPosition();

	FVector2D localMultiplayerButtonAbsoluteCenterPosition();

	FVector2D lanMultiplayerButtonAbsoluteCenterPosition();
};
