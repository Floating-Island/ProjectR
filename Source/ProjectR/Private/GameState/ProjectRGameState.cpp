// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/ProjectRGameState.h"

#include "UI/AnnouncerUI.h"


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
