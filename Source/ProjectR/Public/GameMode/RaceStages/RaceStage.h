// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RaceStage.generated.h"

class ARaceGameMode;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStageEndedEvent, ARaceStage*, broadcasterStage);


UCLASS()
class PROJECTR_API ARaceStage : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ARaceStage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	ARaceGameMode* raceMode;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual ARaceStage* nextStage();

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FStageEndedEvent stageEndedEvent;

	virtual void start();
};
