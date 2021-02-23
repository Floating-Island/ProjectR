// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu.h"
#include "LobbyMenu.generated.h"

class UMapSelectorWidget;
/**
 * 
 */
UCLASS()
class PROJECTR_API ULobbyMenu : public UMenu
{
	GENERATED_BODY()

	
	

protected:
	UFUNCTION()
		void returnToMainMenu();

	UFUNCTION()
		void startRace();

	UPROPERTY(meta = (BindWidget))
		UButton* returnButton;

	UPROPERTY(meta = (BindWidget))
		UMapSelectorWidget* mapListing;

	UPROPERTY(meta = (BindWidget))
		UButton* startRaceButton;

	void focusPlayersOnGame();
	
public:
	virtual bool Initialize() override;
	FVector2D returnButtonAbsoluteCenterPosition();
	FVector2D startRaceButtonAbsoluteCenterPosition();
	
};
