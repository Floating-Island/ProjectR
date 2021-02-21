// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MapSelectorWidget.generated.h"

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

protected:

	UPROPERTY()
		UStringButtonScrollBox* mapListing;

	/// <summary>
	/// Remember that the folders start with /...
	/// </summary>
	UPROPERTY(EditDefaultsOnly)
		FString mapsDirectory;
	
	void createMapButtons();
};
