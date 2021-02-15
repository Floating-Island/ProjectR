// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "../UI/Menu.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
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
	template<class aMenuType>
	aMenuType* loadMenuOfClass(TSubclassOf<UMenu> aMenuClass, FName aMenuName);
	void lockMouseToWidget(UMenu* menu);
	bool menuIsInViewport(UMenu* aMenu);

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
		TSubclassOf<ULanMultiplayerMenu> lanMultiplayerMenuClass;

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

template <class aMenuType>
aMenuType* UProjectRGameInstance::loadMenuOfClass(TSubclassOf<UMenu> aMenuClass, FName aMenuName)
{
	aMenuType* menuInstance = Cast<aMenuType, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), aMenuType::StaticClass()));
	aMenuType* loadedMenu = nullptr;
	if (menuInstance)
	{
		loadedMenu = menuInstance;
	}
	else
	{
		loadedMenu = Cast<aMenuType, UUserWidget>(UUserWidget::CreateWidgetInstance(*GetWorld(), aMenuClass, aMenuName));
	}
	if (!loadedMenu->IsInViewport())
	{
		loadedMenu->AddToViewport();
		lockMouseToWidget(loadedMenu);
	}
	return loadedMenu;
}
