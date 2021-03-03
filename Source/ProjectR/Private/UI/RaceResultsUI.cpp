// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RaceResultsUI.h"

#include "GameState/ProjectRGameState.h"
#include "Components/VerticalBox.h"
#include "PlayerState/RacePlayerState.h"
#include "UI/PlayerPositionRow.h"


void URaceResultsUI::repopulateInfoBox()
{
	infoBox->ClearChildren();
	AProjectRGameState* gameState = Cast<AProjectRGameState, AGameStateBase>(GetWorld()->GetGameState());
	if(gameState && playerPositionRowClass)
	{
		for (const auto& playerState : gameState->PlayerArray)
		{
			ARacePlayerState* raceState = Cast<ARacePlayerState, APlayerState>(playerState);
			if(raceState)
			{
				fillInfoBoxWith(raceState);
			}
		}
	}
}

void URaceResultsUI::fillInfoBoxWith(ARacePlayerState* aRaceState)
{
	UPlayerPositionRow* playerInfoRow = Cast<UPlayerPositionRow, UUserWidget>(CreateWidget(infoBox, playerPositionRowClass));
	if(playerInfoRow)
	{
		playerInfoRow->updateInfoWith(FString::FromInt(aRaceState->GetUniqueID()), FString::FromInt(aRaceState->currentPosition()));
		infoBox->AddChild(playerInfoRow);
	}
}

void URaceResultsUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	repopulateInfoBox();
}

int URaceResultsUI::rowsQuantity()
{
	return infoBox->GetAllChildren().Num();
}
