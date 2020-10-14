// Fill out your copyright notice in the Description page of Project Settings.


#include "Track/TrackGenerator.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

ATrackGenerator::ATrackGenerator()
{
	PrimaryActorTick.bCanEverTick = true;

	splineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	RootComponent = splineComponent;
	splineMeshes = TArray<USplineMeshComponent*>();

	UStaticMesh* roadMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Engine/MapTemplates/SM_Template_Map_Floor")));
}

// Called when the game starts or when spawned
void ATrackGenerator::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATrackGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrackGenerator::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	updateSplineMeshes();
}

int32 ATrackGenerator::nextSplineIndex(int32 currentIndex)
{
	return (currentIndex + 1) % splineComponent->GetNumberOfSplinePoints();
}

void ATrackGenerator::updateSplineMeshes()
{
	splineMeshes.Empty();
	int32 splineQuantity = splineComponent->GetNumberOfSplinePoints();
	for (int32 splinePointIndex = 0; splinePointIndex < splineQuantity; ++splinePointIndex)
	{
		USplineMeshComponent* splineMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(), FName(TEXT("Spline Mesh Component "), splinePointIndex), RF_Transient);
		splineMesh->RegisterComponent();
		splineMeshes.Add(splineMesh);

		splineMeshPositionsAndTangentsSetup(splinePointIndex, splineMesh);
		
		splineMesh->SetStaticMesh(roadMesh);
	}
}

void ATrackGenerator::splineMeshPositionsAndTangentsSetup(int32 splinePointIndex, USplineMeshComponent* splineMesh)
{
	FVector currentSplinePointPosition = splineComponent->GetLocationAtSplinePoint(splinePointIndex, ESplineCoordinateSpace::Local);
	FVector nextSplinePointPosition = splineComponent->GetLocationAtSplinePoint(nextSplineIndex(splinePointIndex), ESplineCoordinateSpace::Local);
	FVector currentSplinePointTangent = splineComponent->GetTangentAtSplinePoint(splinePointIndex, ESplineCoordinateSpace::Local);
	FVector nextSplinePointTangent = splineComponent->GetTangentAtSplinePoint(nextSplineIndex(splinePointIndex), ESplineCoordinateSpace::Local);
	
	splineMesh->SetStartAndEnd(currentSplinePointPosition, currentSplinePointTangent, nextSplinePointPosition, nextSplinePointTangent);
}