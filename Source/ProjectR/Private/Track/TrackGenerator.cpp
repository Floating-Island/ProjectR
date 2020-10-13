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

        splineMeshes.Empty();
	int32 splineQuantity = splineComponent->GetNumberOfSplinePoints();
	for(int32 splinePointIndex =0;splinePointIndex < splineQuantity; ++splinePointIndex)
	{
		UE_LOG(LogTemp, Log, TEXT("current spline point index: %d."), splinePointIndex);
		UE_LOG(LogTemp, Log, TEXT("spline meshes inside splineMeshes array before adding another: %d."), splineMeshes.Num());
		USplineMeshComponent* splineMesh = NewObject<USplineMeshComponent>(this,USplineMeshComponent::StaticClass(), FName(TEXT("Spline Mesh Component %d"), splinePointIndex), RF_Transient);
		splineMesh->RegisterComponent();
		splineMeshes.Add(splineMesh);
		UE_LOG(LogTemp, Log, TEXT("spline meshes inside splineMeshes array after adding another: %d."), splineMeshes.Num());
	}
}

