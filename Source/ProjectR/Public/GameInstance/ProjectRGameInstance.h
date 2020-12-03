// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectRGameInstance.generated.h"

class USingleplayerMenu;
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
	USingleplayerMenu* singleplayerMenu;
public:
	UPROPERTY(EditDefaultsOnly, Category= "Menus")
		TSubclassOf<UMainMenu> mainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category= "Menus")
		TSubclassOf<USingleplayerMenu> singleplayerMenuClass;
	
	UFUNCTION(BlueprintCallable)
	UMainMenu* loadMainMenu();
	
	UFUNCTION(BlueprintCallable)
	USingleplayerMenu* loadSingleplayerMenu();

	bool isMainMenuInViewport();
	bool isSingleplayerMenuInViewport();
};
