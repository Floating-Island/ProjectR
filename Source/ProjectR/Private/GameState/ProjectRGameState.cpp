// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/ProjectRGameState.h"


#include "Net/UnrealNetwork.h"
#include "UI/AnnouncerUI.h"
#include "UI/RaceResultsUI.h"


void AProjectRGameState::fireAnnouncerUpdateEvent()
{
	announcerUpdateEvent.Broadcast(announcerText);
}

void AProjectRGameState::subscribeToAnnouncerUpdate(UAnnouncerUI* anAnnouncerUI)
{
	announcerUpdateEvent.AddUniqueDynamic(anAnnouncerUI, &UAnnouncerUI::modifyWith);
}

void AProjectRGameState::updateAnnouncerWith(FString aText)
{
	announcerText = aText;
	fireAnnouncerUpdateEvent();
}

FString AProjectRGameState::announcerDisplayText()
{
	return announcerText;
}

UClass* AProjectRGameState::announcerUIType()
{
	return announcerUIClass;
}

void AProjectRGameState::fireEvents()
{
	fireAnnouncerUpdateEvent();
}

UClass* AProjectRGameState::resultsUIType()
{
	return resultsUIClass;
}

void AProjectRGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AProjectRGameState, announcerText	);
}
