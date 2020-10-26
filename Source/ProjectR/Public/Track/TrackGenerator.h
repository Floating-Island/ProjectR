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
	
	TArray<USplineMeshComponent*> roadSplines;

	void cleanSplineMeshComponents();
	void destroySplineMeshes();
	void recreateSplineMeshComponents();
	void createSplineMeshes();

	void configureMagnetSpline(int32 aSplinePointIndex, USplineMeshComponent* aRoadSpline, USplineMeshComponent* aMagnetSpline);
	void configureRoadSpline(int32 aSplinePointIndex, USplineMeshComponent* aRoadSpline);
	void configureComponentPositionsAndTangents(int32 aSplinePointIndex, USplineMeshComponent* aSplineMesh);
	void configureCollisionOf(USplineMeshComponent* aMagnetSpline);

	UPROPERTY(EditAnywhere, Category = "Default Meshes")
		UStaticMesh* roadMesh;

	TArray<USplineMeshComponent*> magnetSplines;

	float magnetSplineHeightDistanceToRoadSpline;

	UPROPERTY(EditAnywhere, Category = "Default Meshes")
		UStaticMesh* magnetSplineMesh;

public:

	virtual void OnConstruction(const FTransform& Transform) override;

	int32 nextSplineIndexOf(int32 aCurrentIndex);
	void toMagnetOverlapSubscribe(ATrackManager* aManager);

	FVector closestLocationTo(FVector anotherLocation);
	
};
