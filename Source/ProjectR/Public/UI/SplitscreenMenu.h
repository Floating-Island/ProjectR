// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu.h"
#include "SplitscreenMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API USplitscreenMenu : public UMenu
{
	GENERATED_BODY()

protected:
	
	UFUNCTION()
		void goBack();

	UPROPERTY(meta = (BindWidget))
		UButton* playButton;

	UPROPERTY(meta = (BindWidget))
		UButton* goBackButton;

public:
	virtual bool Initialize() override;
	
	FVector2D goBackButtonAbsoluteCenterPosition();
};
