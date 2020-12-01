// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectRGameInstance.generated.h"

class USoloRaceMenu;
class UMainMenu;
/**
 * 
 */
UCLASS()
class PROJECTR_API UProjectRGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UMainMenu* mainMenu;
	USoloRaceMenu* soloRaceMenu;
public:
	UPROPERTY(EditDefaultsOnly, Category= "Menus")
		TSubclassOf<UMainMenu> mainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category= "Menus")
		TSubclassOf<USoloRaceMenu> soloRaceMenuClass;
	
	UFUNCTION(BlueprintCallable)
	UMainMenu* loadMainMenu();
	
	UFUNCTION(BlueprintCallable)
	USoloRaceMenu* loadSoloRaceMenu();

	bool isMainMenuInViewport();
};
