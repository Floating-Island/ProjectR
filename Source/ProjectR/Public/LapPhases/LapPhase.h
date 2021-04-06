// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LapPhase.generated.h"


UCLASS()
class PROJECTR_API ALapPhase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALapPhase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UStaticMeshComponent* phaseWall;

	UPROPERTY(EditAnywhere, Category = "Phase Wall Mesh")
		UStaticMesh* phaseWallMesh;

	float allowedDistance;

public:

	ALapPhase* updatePhase(ALapPhase* anotherPhase);

	virtual bool nextPhaseIs(ALapPhase* aPhase);

	virtual bool comesFromInitialLapPhase();
	virtual bool comesFromIntermediateLapPhase();
	virtual bool comesFromFinalLapPhase();

	float maximumAllowedDistance();
};
