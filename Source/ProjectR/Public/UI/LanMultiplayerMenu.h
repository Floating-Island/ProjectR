// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu.h"
#include "LanMultiplayerMenu.generated.h"

class UProjectRGameInstance;
class UStringButtonScrollBox;
/**
 * 
 */
UCLASS()
class PROJECTR_API ULanMultiplayerMenu : public UMenu
{
	GENERATED_BODY()

UProjectRGameInstance* gameInstance;
public:
	virtual bool Initialize() override;
	FVector2D goBackButtonAbsoluteCenterPosition();
	FVector2D createSessionButtonAbsoluteCenterPosition();
	void sessionSearchCompletedAnd(bool aSessionSearchWasSuccessful);
	
protected:
	UPROPERTY(meta = (BindWidget))
		UButton* goBackButton;

	UPROPERTY(meta = (BindWidget))
		UButton* createSessionButton;

	UPROPERTY(meta = (BindWidget))
		UStringButtonScrollBox* sessionListingBox;

	UFUNCTION()
		void goBack();

	UFUNCTION()
		void startLANSessionCreation();

	FTimerHandle retrySessionSearchTimer;

	UPROPERTY(EditDefaultsOnly, Category = "Session Search Timer")
		float timeBetweenSearches;
};
