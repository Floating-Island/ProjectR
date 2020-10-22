// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrackManager.generated.h"

class ATrackGenerator;
class AJet;

UCLASS()
class PROJECTR_API ATrackManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrackManager();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TSet<ATrackGenerator*> trackGeneratorSet;
	void collectTrackGenerators();
	TSet<AJet*> jetsToMagnetize;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void addJetToMagnetize (UPrimitiveComponent* OverlappedComponent,
								AActor* OtherActor,
								UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex,
								bool bFromSweep,
								const FHitResult& SweepResult);

	
};


