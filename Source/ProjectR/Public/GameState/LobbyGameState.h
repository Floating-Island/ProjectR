// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGameState.generated.h"

class ULobbyMenu;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLobbyMapUpdateEvent, FString, anUpdatedMap);
/**
 * 
 */
UCLASS()
class PROJECTR_API ALobbyGameState : public AGameStateBase
{
	GENERATED_BODY()


protected:

	UPROPERTY(ReplicatedUsing= fireLobbyMapUpdateEvent)
		FString selectedMap;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
		FLobbyMapUpdateEvent mapUpdateEvent;

	UFUNCTION()
		void fireLobbyMapUpdateEvent();

	
public:
	UFUNCTION()
		void updateSelectedMap(FString anUpdatedMap);

	void subscribeToLobbyMapUpdate(ULobbyMenu* aLobbyMenu);
};
