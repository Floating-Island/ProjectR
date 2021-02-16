// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu.h"
#include "LanMultiplayerMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API ULanMultiplayerMenu : public UMenu
{
	GENERATED_BODY()


public:
	virtual bool Initialize() override;
	FVector2D goBackButtonAbsoluteCenterPosition();

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* goBackButton;

	UFUNCTION()
		void goBack();
};
