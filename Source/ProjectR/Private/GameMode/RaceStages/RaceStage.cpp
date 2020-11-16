// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/RaceStages/RaceStage.h"
#include "GameMode/RaceGameMode.h"

// Sets default values
ARaceStage::ARaceStage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARaceStage::BeginPlay()
{
	Super::BeginPlay();
	raceMode = Cast<ARaceGameMode, AGameModeBase>(GetWorld()->GetAuthGameMode());
	stageEndedEvent.AddDynamic(raceMode, &ARaceGameMode::stageUpdate);
}

// Called every frame
void ARaceStage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ARaceStage* ARaceStage::nextStage()
{
	return this;
}

