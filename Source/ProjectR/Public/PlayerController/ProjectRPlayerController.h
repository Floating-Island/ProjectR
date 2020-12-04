// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProjectRPlayerController.generated.h"

class UPauseMenu;
/**
 * 
 */
UCLASS()
class PROJECTR_API AProjectRPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPauseMenu* pauseMenu;

	virtual void SetupInputComponent() override;

public:
	AProjectRPlayerController(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditDefaultsOnly, Category= "Menus")
		TSubclassOf<UPauseMenu> pauseMenuClass;

	UPauseMenu* loadPauseMenu();

	UFUNCTION()
		void loadPauseMenuWrapper();
};
