// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LapManager.generated.h"


class AJet;

UCLASS()
class PROJECTR_API ALapManager : public AActor
{
	GENERATED_BODY()

private:
	TSet<AJet*> jetLaps;
	void storeJetsFromWorld();
public:	
	// Sets default values for this actor's properties
	ALapManager();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TSet<AJet*> jetsInPlay();

};