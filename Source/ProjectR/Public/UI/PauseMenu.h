// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu.h"
#include "PauseMenu.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTR_API UPauseMenu : public UMenu
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
		UButton* returnButton;

	UFUNCTION()
		void returnToMainMenu();

	UPROPERTY(EditAnywhere, Category="Menu Map")
		FName mainMenuLevel;

	UPROPERTY(meta = (BindWidget))
		UButton* resumeButton;

	UFUNCTION()
		void removeFromViewportAndResumeGame();
	
	void focusOnGame();
	
public:
	FVector2D returnButtonAbsoluteCenterPosition();

	FVector2D resumeButtonAbsoluteCenterPosition();

	virtual bool Initialize() override;
};
