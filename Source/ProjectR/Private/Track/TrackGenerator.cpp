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

	updateSplineMeshesQuantity();
}

int32 ATrackGenerator::nextSplineIndex(int32 currentIndex)
{
	return (currentIndex + 1) % splineComponent->GetNumberOfSplinePoints();
}

void ATrackGenerator::updateSplineMeshesQuantity()
{
	splineMeshes.Empty();
	int32 splineQuantity = splineComponent->GetNumberOfSplinePoints();
	for (int32 splinePointIndex = 0; splinePointIndex < splineQuantity; ++splinePointIndex)
	{
		USplineMeshComponent* splineMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(), FName(TEXT("Spline Mesh Component "), splinePointIndex), RF_Transient);
		splineMesh->RegisterComponent();
		splineMeshes.Add(splineMesh);

		FVector currentSplinePointPosition = splineComponent->GetLocationAtSplinePoint(splinePointIndex, ESplineCoordinateSpace::World);
		splineMesh->SetStartPosition(currentSplinePointPosition);
		FVector nextSplinePointPosition = splineComponent->GetLocationAtSplinePoint(nextSplineIndex(splinePointIndex), ESplineCoordinateSpace::World);
		splineMesh->SetEndPosition(nextSplinePointPosition);
		FVector currentSplinePointTangent = splineComponent->GetTangentAtSplinePoint(splinePointIndex, ESplineCoordinateSpace::World);
		splineMesh->SetStartTangent(currentSplinePointTangent);
	}
}
