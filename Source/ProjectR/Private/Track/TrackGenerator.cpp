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

void ATrackGenerator::splineMeshSetup(int32 aSplinePointIndex, USplineMeshComponent* aSplineMesh)
{
	aSplineMesh->RegisterComponent();
	splineMeshes.Add(aSplineMesh);

	componentPositionsAndTangentsSetup(aSplinePointIndex, aSplineMesh);

	aSplineMesh->SetStaticMesh(roadMesh);

	aSplineMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	aSplineMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	aSplineMesh->Mobility = RootComponent->Mobility;
	aSplineMesh->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}

void ATrackGenerator::componentPositionsAndTangentsSetup(int32 aSplinePointIndex, USplineMeshComponent* aSplineMesh)
{
	FVector currentSplinePointPosition = splineComponent->GetLocationAtSplinePoint(aSplinePointIndex, ESplineCoordinateSpace::Local);
	FVector nextSplinePointPosition = splineComponent->GetLocationAtSplinePoint(nextSplineIndex(aSplinePointIndex), ESplineCoordinateSpace::Local);
	FVector currentSplinePointTangent = splineComponent->GetTangentAtSplinePoint(aSplinePointIndex, ESplineCoordinateSpace::Local);
	FVector nextSplinePointTangent = splineComponent->GetTangentAtSplinePoint(nextSplineIndex(aSplinePointIndex), ESplineCoordinateSpace::Local);

	aSplineMesh->SetStartAndEnd(currentSplinePointPosition, currentSplinePointTangent, nextSplinePointPosition, nextSplinePointTangent);
}

void ATrackGenerator::magnetBoxSetup(int32 aSplinePointIndex, USplineMeshComponent* aSplineMesh, USplineMeshComponent* aMagnetBox)
{
	aMagnetBox->RegisterComponent();
	magnetBoxes.Add(aMagnetBox);
	aMagnetBox->Mobility = aSplineMesh->Mobility; 

	aMagnetBox->SetHiddenInGame(true);
	
	componentPositionsAndTangentsSetup(aSplinePointIndex, aMagnetBox);

	aMagnetBox->SetStaticMesh(magnetBoxMesh);

	//aMagnetBox->SetStartScale(aMagnetBox->GetStartScale()*5);//should be removed once the initial bounds Z extension is known (of a mesh created for it)...
	//aMagnetBox->SetEndScale(aMagnetBox->GetEndScale()*5);//should be removed once the initial bounds Z extension is known (of a mesh created for it)...
	
	aMagnetBox->AttachToComponent(aSplineMesh,FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	FVector magnetBoxHeight = FVector(0,0, magnetBoxHeightDistanceToSplineMesh);
		
	aMagnetBox->SetStartPosition(aMagnetBox->GetStartPosition() + magnetBoxHeight);
	aMagnetBox->SetEndPosition(aMagnetBox->GetEndPosition() + magnetBoxHeight);
}