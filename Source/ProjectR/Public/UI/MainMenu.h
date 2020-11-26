// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class PROJECTR_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION()
		void quit();

	UPROPERTY(meta = (BindWidget))
		UButton* quitButton;

public:
	virtual bool Initialize() override;

	FVector2D quitButtonPosition();
	
};
