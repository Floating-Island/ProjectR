// Fill out your copyright notice in the Description page of Project Settings.


#include "Track/TrackGenerator.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Track/TrackManager.h"

ATrackGenerator::ATrackGenerator()
{
	bGenerateOverlapEventsDuringLevelStreaming = true;
	splineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	RootComponent = splineComponent;
	roadSplines = TArray<USplineMeshComponent*>();

	roadMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Development/Models/roadFloor")));

	magnetSplines = TArray<USplineMeshComponent*>();

	splineComponent->SetClosedLoop(true, true);

	magnetSplineHeightDistanceToRoadSpline = 400.0f;

	magnetSplineMesh = roadMesh;

	rollArray = TArray<float>();
}



// Called when the game starts or when spawned
void ATrackGenerator::BeginPlay()
{
	Super::BeginPlay();
	recreateSplineMeshComponents();
}

void ATrackGenerator::recreateSplineMeshComponents()
{
	adjustRollArraySizeToSplinePointsQuantity();
	cleanSplineMeshComponents();
	createSplineMeshComponents();
}

void ATrackGenerator::adjustRollArraySizeToSplinePointsQuantity()
{
	int quantityDifference = splineComponent->GetNumberOfSplinePoints() - rollArray.Num();
	if (quantityDifference > 0)
	{
		for (int addedElements = 0; addedElements < quantityDifference; ++addedElements)
		{
			rollArray.Add(0);
		}
		return;
	}
	if (quantityDifference < 0)
	{
		quantityDifference = abs(quantityDifference);
		for (int removedElements = 0; removedElements < quantityDifference; ++removedElements)
		{
			rollArray.Pop(true);
		}
		return;
	}
}

void ATrackGenerator::cleanSplineMeshComponents()
{
	destroySplineMeshComponents();
	roadSplines.Empty();
	magnetSplines.Empty();
}

void ATrackGenerator::destroySplineMeshComponents()
{
	for (auto roadSpline : roadSplines)
	{
		roadSpline->DestroyComponent();
	}
	for (auto magnetSpline : magnetSplines)
	{
		magnetSpline->DestroyComponent();
	}
}



void ATrackGenerator::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	recreateSplineMeshComponents();
}

int32 ATrackGenerator::nextSplineIndexOf(int32 aCurrentIndex)
{
	return (aCurrentIndex + 1) % splineComponent->GetNumberOfSplinePoints();
}

void ATrackGenerator::toMagnetOverlapSubscribe(ATrackManager* aManager)
{
	for (auto magnetMesh : magnetSplines)
	{
		magnetMesh->OnComponentBeginOverlap.AddDynamic(aManager, &ATrackManager::addJetToMagnetize);
	}
}

FVector ATrackGenerator::closestLocationTo(FVector anotherLocation)
{
	return splineComponent->FindLocationClosestToWorldLocation(anotherLocation, ESplineCoordinateSpace::World);
}

void ATrackGenerator::createSplineMeshComponents()
{
	int32 splineQuantity = splineComponent->GetNumberOfSplinePoints();
	for (int32 splinePointIndex = 0; splinePointIndex < splineQuantity; ++splinePointIndex)
	{
		USplineMeshComponent* roadSpline = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(), FName(TEXT("Spline Mesh Component "), splinePointIndex));
		configureRoadSpline(splinePointIndex, roadSpline);

		USplineMeshComponent* magnetSpline = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(), FName(TEXT("Magnet Box Component "), splinePointIndex));
		configureMagnetSpline(splinePointIndex, roadSpline, magnetSpline);
	}
}

void ATrackGenerator::configureRoadSpline(int32 aSplinePointIndex, USplineMeshComponent* aRoadSpline)
{
	aRoadSpline->RegisterComponent();
	roadSplines.Add(aRoadSpline);

	aRoadSpline->bSmoothInterpRollScale = true;

	configureComponentPositionsAndTangents(aSplinePointIndex, aRoadSpline);

	aRoadSpline->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	aRoadSpline->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	aRoadSpline->Mobility = RootComponent->Mobility;
	aRoadSpline->SetStaticMesh(roadMesh);
	aRoadSpline->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}

void ATrackGenerator::configureComponentPositionsAndTangents(int32 aSplinePointIndex, USplineMeshComponent* aSplineMesh)
{
	FVector currentSplinePointPosition = splineComponent->GetLocationAtSplinePoint(aSplinePointIndex, ESplineCoordinateSpace::Local);
	FVector nextSplinePointPosition = splineComponent->GetLocationAtSplinePoint(nextSplineIndexOf(aSplinePointIndex), ESplineCoordinateSpace::Local);
	FVector currentSplinePointTangent = splineComponent->GetTangentAtSplinePoint(aSplinePointIndex, ESplineCoordinateSpace::Local);
	FVector nextSplinePointTangent = splineComponent->GetTangentAtSplinePoint(nextSplineIndexOf(aSplinePointIndex), ESplineCoordinateSpace::Local);

	aSplineMesh->SetStartAndEnd(currentSplinePointPosition, currentSplinePointTangent, nextSplinePointPosition, nextSplinePointTangent);
}

void ATrackGenerator::configureMagnetSpline(int32 aSplinePointIndex, USplineMeshComponent* aRoadSpline, USplineMeshComponent* aMagnetSpline)
{
	aMagnetSpline->RegisterComponent();
	magnetSplines.Add(aMagnetSpline);

	aMagnetSpline->Mobility = aRoadSpline->Mobility;

	aMagnetSpline->SetHiddenInGame(true);

	aMagnetSpline->bSmoothInterpRollScale = true;

	configureComponentPositionsAndTangents(aSplinePointIndex, aMagnetSpline);

	aMagnetSpline->SetStaticMesh(magnetSplineMesh);

	//aMagnetBox->SetStartScale(aMagnetBox->GetStartScale()*5);//should be removed once the initial bounds Z extension is known (of a mesh created for it)...
	//aMagnetBox->SetEndScale(aMagnetBox->GetEndScale()*5);//should be removed once the initial bounds Z extension is known (of a mesh created for it)...

	aMagnetSpline->AttachToComponent(aRoadSpline, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	FVector magnetSplineHeight = FVector(0, 0, magnetSplineHeightDistanceToRoadSpline);

	aMagnetSpline->SetStartPosition(aMagnetSpline->GetStartPosition() + magnetSplineHeight);
	aMagnetSpline->SetEndPosition(aMagnetSpline->GetEndPosition() + magnetSplineHeight);

	configureCollisionOf(aMagnetSpline);
}

void ATrackGenerator::configureCollisionOf(USplineMeshComponent* aMagnetSpline)
{
	aMagnetSpline->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	aMagnetSpline->SetCollisionResponseToAllChannels(ECR_Ignore);
	aMagnetSpline->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	aMagnetSpline->SetGenerateOverlapEvents(true);
}