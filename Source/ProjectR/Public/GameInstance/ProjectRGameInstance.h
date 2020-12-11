// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../UI/Menu.h"
#include "Engine/GameInstance.h"
#include "ProjectRGameInstance.generated.h"

class USplitscreenMenu;
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
	int numberOfPlayers;
	UMainMenu* mainMenu;
	USingleplayerMenu* singleplayerMenu;
	USplitscreenMenu* splitscreenMenu;
	void lockMouseToWidget(UMenu* menu);
public:
	UProjectRGameInstance();
	
	UPROPERTY(EditDefaultsOnly, Category= "Menus")
		TSubclassOf<UMainMenu> mainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category= "Menus")
		TSubclassOf<USingleplayerMenu> singleplayerMenuClass;

	UPROPERTY(EditDefaultsOnly, Category= "Menus")
		TSubclassOf<USplitscreenMenu> splitscreenMenuClass;

	UFUNCTION(BlueprintCallable)
	UMainMenu* loadMainMenu();
	
	UFUNCTION(BlueprintCallable)
	USingleplayerMenu* loadSingleplayerMenu();

	UFUNCTION(BlueprintCallable)
	USplitscreenMenu* loadSplitscreenMenu();

	bool isMainMenuInViewport();
	bool isSingleplayerMenuInViewport();

	void expectedPlayers(int aQuantity);
	int necessaryPlayers();
};
