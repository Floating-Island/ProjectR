// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProjectRPlayerController.generated.h"

class AProjectRGameState;
class UAnnouncerUI;
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

	UPROPERTY()
		UAnnouncerUI* announcerUI;

	void showRaceUI();

	UFUNCTION()
		void configureRaceUI();

	void configureAnnouncerUI(AProjectRGameState* aGameState);
	void showAnnouncerUI();
	

public:
	AProjectRPlayerController(const FObjectInitializer& ObjectInitializer);
	void focusOnGame();
	void focusOnPauseMenu();

	UFUNCTION(Client, Reliable)
		void loadRaceUI();

	UPROPERTY(EditDefaultsOnly, Category= "Menus")
		TSubclassOf<UPauseMenu> pauseMenuClass;

	UPauseMenu* loadPauseMenu();

	UFUNCTION()
		void loadPauseMenuWrapper();

	UFUNCTION(Client, Reliable)
		void loadAnnouncerUI();

	void removeAnnouncerUI();
};
