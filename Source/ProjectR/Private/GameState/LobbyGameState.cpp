// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/LobbyGameState.h"

#include "../../Public/UI/LobbyMenu.h"
#include "Net/UnrealNetwork.h"

void ALobbyGameState::fireLobbyMapUpdateEvent()
{
	mapUpdateEvent.Broadcast(selectedMap);
}

void ALobbyGameState::updateSelectedMap(FString anUpdatedMap)
{
	if(HasAuthority())
	{
		selectedMap = anUpdatedMap;
	}
}

void ALobbyGameState::subscribeToLobbyMapUpdate(ULobbyMenu* aLobbyMenu)
{
	mapUpdateEvent.AddUniqueDynamic(aLobbyMenu, &ULobbyMenu::updateSelectedMapText);
	fireLobbyMapUpdateEvent();
}

FString ALobbyGameState::selectedMapName()
{
	return selectedMap;
}


void ALobbyGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ALobbyGameState, selectedMap);
}
