// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Track.generated.h"

UCLASS()
class PROJECTR_API ATrack : public AActor
{
	GENERATED_BODY()

public:
	/*void matchMagnetBoxXYExtensionToFloor();*/
	// Sets default values for this actor's properties
	ATrack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* floorComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* magnetBox;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
