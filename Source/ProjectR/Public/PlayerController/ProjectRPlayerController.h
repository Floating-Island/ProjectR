// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProjectRPlayerController.generated.h"

class URacePlayerUI;
class UPauseMenu;
/**
 * 
 */
UCLASS()
class PROJECTR_API AProjectRPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		UPauseMenu* pauseMenu;

	virtual void SetupInputComponent() override;


	UPROPERTY()
		URacePlayerUI* raceUI;

	void showRaceUI();

	UFUNCTION()
		void configureRaceUI();
	

public:
	AProjectRPlayerController(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	void focusOnGame();
	void focusOnPauseMenu();

	UFUNCTION(Client, Reliable)
		void loadRaceUI();

	UPROPERTY(EditDefaultsOnly, Category= "Menus")
		TSubclassOf<UPauseMenu> pauseMenuClass;

	UPauseMenu* loadPauseMenu();

	UFUNCTION()
		void loadPauseMenuWrapper();
};
