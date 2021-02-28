// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "UI/RacePlayerUI.h"
#include "RacePlayerState.generated.h"


class AProjectRPlayerController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLapUpdateEvent, int, anUpdatedLap);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPositionUpdateEvent, int, anUpdatedPosition);
/**
 * 
 */
UCLASS()
class PROJECTR_API ARacePlayerState : public APlayerState
{
	GENERATED_BODY()

protected:


	UPROPERTY(ReplicatedUsing= fireLapUpdateEvent)
		int lap;
	
	int position;
	int totalLapsValue;

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FLapUpdateEvent lapUpdateEvent;

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FPositionUpdateEvent positionUpdateEvent;

	UFUNCTION()
		void fireLapUpdateEvent();
	
	void firePositionUpdateEvent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
		TSubclassOf<URacePlayerUI> raceUIClass;
	
public:
	ARacePlayerState();
	int currentLap();
	void updateLapTo(int aCurrentLap);
	int currentPosition();
	void updatePositionTo(int aCurrentPosition);
	void subscribeToLapUpdate(URacePlayerUI* aRacePlayerUI);
	void subscribeToPositionUpdate(URacePlayerUI* aRacePlayerUI);
	int totalLaps();
	void setTotalLapsTo(int aDesiredAmount);
	UClass* raceUIType();
	void fireEvents(APlayerController* controller);
	
};
