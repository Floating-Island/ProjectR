// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../UI/Menu.h"
#include "Engine/GameInstance.h"
#include "ProjectRGameInstance.generated.h"

class ULanMultiplayerMenu;
class USessionManager;
class ULocalMultiplayerMenu;
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
	ULocalMultiplayerMenu* localMultiplayerMenu;
	ULanMultiplayerMenu* lanMultiplayerMenu;
	void lockMouseToWidget(UMenu* menu);

	UPROPERTY()
	USessionManager* sessionManager;
	
public:
	UProjectRGameInstance();
	
	UPROPERTY(EditDefaultsOnly, Category= "Menus")
		TSubclassOf<UMainMenu> mainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category= "Menus")
		TSubclassOf<USingleplayerMenu> singleplayerMenuClass;

	UPROPERTY(EditDefaultsOnly, Category= "Menus")
		TSubclassOf<ULocalMultiplayerMenu> localMultiplayerMenuClass;

	UPROPERTY(EditDefaultsOnly, Category= "Menus")
		TSubclassOf<ULocalMultiplayerMenu> lanMultiplayerMenuClass;

	UFUNCTION(BlueprintCallable)
	UMainMenu* loadMainMenu();
	
	UFUNCTION(BlueprintCallable)
	USingleplayerMenu* loadSingleplayerMenu();

	UFUNCTION(BlueprintCallable)
	ULocalMultiplayerMenu* loadLocalMultiplayerMenu();

	UFUNCTION(BlueprintCallable)
	ULanMultiplayerMenu* loadLANMUltiplayerMenu();

	bool isMainMenuInViewport();
	bool isSingleplayerMenuInViewport();
	bool isLocalMultiplayerMenuInViewport();

	void expectedPlayers(int aQuantity);
	int necessaryPlayers();
	bool sessionManagerIsConfigured();

	virtual void OnStart() override;
};
