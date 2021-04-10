// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrackGenerator.generated.h"



class USplineComponent;
class USplineMeshComponent;
class ATrackManager;

USTRUCT()
struct FTrackSectionData
{
	GENERATED_BODY()

	USplineMeshComponent* roadSpline = nullptr;
	USplineMeshComponent* magnetSpline = nullptr;
	USplineMeshComponent* boundsSpline = nullptr;

	UPROPERTY(EditAnywhere, Category = "Default Meshes")
		UStaticMesh* roadMesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Default Meshes")
		UStaticMesh* magnetMesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Default Meshes")
		UStaticMesh* boundsMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Section")
		float startRoll = 0;
	UPROPERTY(EditAnywhere, Category = "Section")
		float initialWidth = 1;
};

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

	void recreateSplineMeshComponents();
	void adjustRollArraySizeToSplinePointsQuantity();
	void cleanSplineMeshComponents();
	void destroySplineMeshComponents();
	void createSplineMeshComponents();
	void editorCollisionsEnabled(USplineMeshComponent* aSplineMeshComponent);

	void configureRoadSpline(int32 aSplinePointIndex, USplineMeshComponent* aRoadSpline);
	void configureMagnetSpline(int32 aSplinePointIndex, USplineMeshComponent* aRoadSpline, USplineMeshComponent* aMagnetSpline);
	void configureBoundsSpline(int32 aSplinePointIndex, USplineMeshComponent* aRoadSpline, USplineMeshComponent* aBoundsSpline);
	void configureComponentPositionsAndTangents(int32 aSplinePointIndex, USplineMeshComponent* aSplineMesh);
	void configureRollAndWidthOf(USplineMeshComponent* aSplineMeshComponent, int32 AtASplinePointIndex);
	void configureCollisionOf(USplineMeshComponent* aMagnetSpline);

	UPROPERTY(EditAnywhere, Category = "Default Settings")
		UStaticMesh* defaultRoadMesh;

	UPROPERTY(EditAnywhere, Category = "Default Settings")
		UStaticMesh* defaultMagnetMesh;

	UPROPERTY(EditAnywhere, Category = "Default Settings")
		UStaticMesh* defaultBoundsMesh;

	
	float magnetSplineHeightDistanceToRoadSpline;
	
	UPROPERTY(EditAnywhere, Category = "Elements", EditFixedSize)
		TArray<FTrackSectionData> trackSections;

	UPROPERTY(EditAnywhere, Category = "Default Settings")
		bool collisionsEnabled;

	void trackManagerSubscription();

public:

	virtual void OnConstruction(const FTransform& Transform) override;

	int32 nextSplineIndexOf(int32 aCurrentIndex);

	FVector closestLocationTo(FVector anotherLocation);
	void toMagnetOverlapSubscribe(ATrackManager* aManager);

	float distanceAlongSplineOf(AActor* anActor);

	float length();

	FVector rightVectorAt(float aDistanceAlongSpline);
	FVector locationAt(float aDistanceAlongSpline);
	FVector upVectorAt(float aDistanceAlongSpline);
	FVector upVectorAt(FVector aNearWorldLocationToSpline);
	FRotator rotationAt(float aDistanceAlongSpline);

};



