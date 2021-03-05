// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu.h"
#include "LobbyMenu.generated.h"

class UTextBlock;
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

	UPROPERTY(meta = (BindWidget))
		UTextBlock* playersInLobbyText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* selectedMapText;

	void focusPlayersOnGame();
	void updatePlayersInLobby();
	bool localOwnerHasAuthority();

	UFUNCTION()
		void subscribeGameStateToMapUpdateEvent();


public:
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	FVector2D returnButtonAbsoluteCenterPosition();
	FVector2D startRaceButtonAbsoluteCenterPosition();
	UFUNCTION()
		void updateSelectedMapText(FString aText);

	int connectedPlayers();
	FString selectedMap();
	
};
