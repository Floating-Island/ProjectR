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

	roadMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Engine/MapTemplates/SM_Template_Map_Floor")));

	magnetBoxes = TArray<USplineMeshComponent*>();

	splineComponent->SetClosedLoop(true, true);

	magnetBoxHeightDistanceToSplineMesh = 400.0f;

	magnetBoxMesh = roadMesh;
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
		USplineMeshComponent* splineMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(), FName(TEXT("Spline Mesh Component "), splinePointIndex), RF_DefaultSubObject);
		splineMeshSetup(splinePointIndex, splineMesh);
		
		USplineMeshComponent* magnetBox = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(), FName(TEXT("Magnet Box Component "), splinePointIndex), RF_DefaultSubObject);
		magnetBoxSetup(splinePointIndex, splineMesh, magnetBox);
	}
}

void ATrackGenerator::splineMeshSetup(int32 splinePointIndex, USplineMeshComponent* splineMesh)
{
	splineMesh->RegisterComponent();
	splineMeshes.Add(splineMesh);

	componentPositionsAndTangentsSetup(splinePointIndex, splineMesh);

	splineMesh->SetStaticMesh(roadMesh);

	splineMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	splineMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	splineMesh->Mobility = RootComponent->Mobility;
	splineMesh->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
}

void ATrackGenerator::componentPositionsAndTangentsSetup(int32 splinePointIndex, USplineMeshComponent* splineMesh)
{
	FVector currentSplinePointPosition = splineComponent->GetLocationAtSplinePoint(splinePointIndex, ESplineCoordinateSpace::World);
	FVector nextSplinePointPosition = splineComponent->GetLocationAtSplinePoint(nextSplineIndex(splinePointIndex), ESplineCoordinateSpace::World);
	FVector currentSplinePointTangent = splineComponent->GetTangentAtSplinePoint(splinePointIndex, ESplineCoordinateSpace::World);
	FVector nextSplinePointTangent = splineComponent->GetTangentAtSplinePoint(nextSplineIndex(splinePointIndex), ESplineCoordinateSpace::World);

	splineMesh->SetStartAndEnd(currentSplinePointPosition, currentSplinePointTangent, nextSplinePointPosition, nextSplinePointTangent);
}

void ATrackGenerator::magnetBoxSetup(int32 splinePointIndex, USplineMeshComponent* splineMesh, USplineMeshComponent* magnetBox)
{
	magnetBox->RegisterComponent();
	magnetBoxes.Add(magnetBox);
	magnetBox->Mobility = splineMesh->Mobility; 

	magnetBox->SetHiddenInGame(true);
	
	componentPositionsAndTangentsSetup(splinePointIndex, magnetBox);

	magnetBox->SetStaticMesh(magnetBoxMesh);
	
	magnetBox->AttachToComponent(splineMesh,FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));

	FVector magnetBoxHeight = FVector(0,0, magnetBoxHeightDistanceToSplineMesh);
		
	magnetBox->SetStartPosition(magnetBox->GetStartPosition() + magnetBoxHeight);
	magnetBox->SetEndPosition(magnetBox->GetEndPosition() + magnetBoxHeight);
}