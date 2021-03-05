// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "StringButtonScrollBox.h"
#include "Blueprint/UserWidget.h"
#include "MapSelectorWidget.generated.h"

class ULobbyMenu;
class ALobbyGameState;
class UStringButtonScrollBox;
/**
 * 
 */
UCLASS()
class PROJECTR_API UMapSelectorWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;
	TArray<FString> mapsCollected();
	FString selectedMap();

	void subscribeToMapUpdate(ALobbyGameState* aGameState);
	void subscribeToMapUpdate(ULobbyMenu* ALobbyMenu);
	
protected:

	UPROPERTY(meta = (BindWidget))
		UStringButtonScrollBox* mapListing;

	/// <summary>
	/// Remember that the folders start with /...
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
		FString mapsDirectory;
	
	void createMapButtons();
};
