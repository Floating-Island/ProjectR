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
		TMap<FString, int> namesAndPositions = TMap<FString, int>();
		for (const auto& playerState : gameState->PlayerArray)
		{
			ARacePlayerState* raceState = Cast<ARacePlayerState, APlayerState>(playerState);
			if(raceState)
			{
				namesAndPositions.Add(FString::FromInt(raceState->GetUniqueID()), raceState->currentPosition());
			}
		}
		namesAndPositions.ValueSort([](float first, float second) {return first < second; });
		
		for (const auto& playerInfo : namesAndPositions)
		{
			fillInfoBoxWith(playerInfo);
		}
	}
}

void URaceResultsUI::fillInfoBoxWith(const TTuple<FString, int>& aPlayerNameAndPositionTuple)
{
	UPlayerPositionRow* playerInfoRow = Cast<UPlayerPositionRow, UUserWidget>(CreateWidget(infoBox, playerPositionRowClass));
	if(playerInfoRow)
	{
		playerInfoRow->updateInfoWith(aPlayerNameAndPositionTuple.Key, FString::FromInt(aPlayerNameAndPositionTuple.Value));
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
