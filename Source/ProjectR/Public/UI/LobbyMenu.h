// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Menu.h"
#include "LobbyMenu.generated.h"

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


	
	UPROPERTY(meta = (BindWidget))
		UButton* returnButton;

public:
	virtual bool Initialize() override;
	FVector2D returnButtonAbsoluteCenterPosition();
	
};
