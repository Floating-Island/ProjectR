// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ProjectRGameState.generated.h"

class URaceResultsUI;
class UAnnouncerUI;
class UPauseMenu;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAnnouncerUpdateEvent, FString, anUpdatedText);
/**
 * 
 */
UCLASS()
class PROJECTR_API AProjectRGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(ReplicatedUsing= fireAnnouncerUpdateEvent)
		FString announcerText;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FAnnouncerUpdateEvent announcerUpdateEvent;

	UFUNCTION()
		void fireAnnouncerUpdateEvent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
		TSubclassOf<UAnnouncerUI> announcerUIClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
		TSubclassOf<URaceResultsUI> resultsUIClass;
	
//public:
//	UPROPERTY(EditDefaultsOnly, Category= "Menus")
//		TSubclassOf<UPauseMenu> pauseMenuClass;

public:
	void subscribeToAnnouncerUpdate(UAnnouncerUI* anAnnouncerUI);
	void updateAnnouncerWith(FString aText);
	FString announcerDisplayText();
	UClass* announcerUIType();
	void fireEvents();
	UClass* resultsUIType();
};
