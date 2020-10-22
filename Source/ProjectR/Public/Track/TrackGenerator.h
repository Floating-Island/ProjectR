// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrackGenerator.generated.h"



class USplineComponent;
class USplineMeshComponent;
class ATrackManager;

UCLASS()
class PROJECTR_API ATrackGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrackGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")	
		USplineComponent* splineComponent;
	
	TArray<USplineMeshComponent*> splineMeshes;

	void updateSplineMeshes();

	void configureMagnetBox(int32 splinePointIndex, USplineMeshComponent* splineMesh, USplineMeshComponent* magnetBox);
	void configureSplineMesh(int32 splinePointIndex, USplineMeshComponent* splineMesh);
	void configureComponentPositionsAndTangents(int32 splinePointIndex, USplineMeshComponent* splineMesh);
	void configureCollisionOf(USplineMeshComponent* aMagnetBox);

	UPROPERTY(EditAnywhere, Category = "Default Meshes")
		UStaticMesh* roadMesh;

	TArray<USplineMeshComponent*> magnetBoxes;

	float magnetBoxHeightDistanceToSplineMesh;

	UPROPERTY(EditAnywhere, Category = "Default Meshes")
		UStaticMesh* magnetBoxMesh;

public:

	virtual void OnConstruction(const FTransform& Transform) override;

	int32 nextSplineIndex(int32 currentIndex);
	void toMagnetOverlapSubscribe(ATrackManager* manager);

	FVector closestLocationTo(FVector anotherLocation);
	
};
