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

	roadMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Development/Models/roadFloor")));


	splineComponent->SetClosedLoop(true, true);

	magnetSplineHeightDistanceToRoadSpline = 400.0f;

	magnetSplineMesh = roadMesh;

	trackSections = TArray<FTrackSectionData>();
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
	int quantityDifference = splineComponent->GetNumberOfSplinePoints() - trackSections.Num();
	if (quantityDifference > 0)
	{
		for (int addedElements = 0; addedElements < quantityDifference; ++addedElements)
		{
			trackSections.Add(FTrackSectionData());
			trackSections.Last().roadMesh = roadMesh;
			trackSections.Last().magnetMesh = magnetSplineMesh;
		}
		return;
	}
	if (quantityDifference < 0)
	{
		quantityDifference = abs(quantityDifference);
		for (int removedElements = 0; removedElements < quantityDifference; ++removedElements)
		{
			trackSections.Pop(true);
		}
		return;
	}
}

void ATrackGenerator::cleanSplineMeshComponents()
{
	destroySplineMeshComponents();
	for (auto& trackSection : trackSections)
	{
		trackSection.roadSpline = nullptr;
		trackSection.magnetSpline = nullptr;
	}
}

void ATrackGenerator::destroySplineMeshComponents()
{
	for (auto& trackSection : trackSections)
	{
		if (trackSection.roadSpline)
		{
			trackSection.roadSpline->DestroyComponent();
		}
		if (trackSection.magnetSpline)
		{
			trackSection.magnetSpline->DestroyComponent();
		}
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
	for (auto& trackSection : trackSections)
	{
		trackSection.magnetSpline->OnComponentBeginOverlap.AddDynamic(aManager, &ATrackManager::addJetToMagnetize);
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
		USplineMeshComponent* roadSpline = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(), FName(TEXT("Road Spline Component "), splinePointIndex));
		configureRoadSpline(splinePointIndex, roadSpline);

		USplineMeshComponent* magnetSpline = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(), FName(TEXT("Magnet Spline Component "), splinePointIndex));
		configureMagnetSpline(splinePointIndex, roadSpline, magnetSpline);
	}
}

void ATrackGenerator::configureRoadSpline(int32 aSplinePointIndex, USplineMeshComponent* aRoadSpline)
{
	aRoadSpline->RegisterComponent();
	trackSections[aSplinePointIndex].roadSpline = aRoadSpline;

	aRoadSpline->bSmoothInterpRollScale = true;

	configureComponentPositionsAndTangents(aSplinePointIndex, aRoadSpline);

	aRoadSpline->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	aRoadSpline->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	aRoadSpline->Mobility = RootComponent->Mobility;

	aRoadSpline->SetStaticMesh(trackSections[aSplinePointIndex].roadMesh);

	aRoadSpline->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	aRoadSpline->SetStartRoll(trackSections[aSplinePointIndex].startRoll);
	aRoadSpline->SetEndRoll(trackSections[nextSplineIndexOf(aSplinePointIndex)].startRoll);
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
	trackSections[aSplinePointIndex].magnetSpline = aMagnetSpline;

	aMagnetSpline->Mobility = aRoadSpline->Mobility;

	aMagnetSpline->SetHiddenInGame(true);

	aMagnetSpline->bSmoothInterpRollScale = true;

	configureComponentPositionsAndTangents(aSplinePointIndex, aMagnetSpline);

	aMagnetSpline->SetStaticMesh(trackSections[aSplinePointIndex].magnetMesh);

	//aMagnetBox->SetStartScale(aMagnetBox->GetStartScale()*5);//should be removed once the initial bounds Z extension is known (of a mesh created for it)...
	//aMagnetBox->SetEndScale(aMagnetBox->GetEndScale()*5);//should be removed once the initial bounds Z extension is known (of a mesh created for it)...

	aMagnetSpline->AttachToComponent(aRoadSpline, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	FVector magnetSplineHeight = FVector(0, 0, magnetSplineHeightDistanceToRoadSpline);

	aMagnetSpline->SetStartPosition(aMagnetSpline->GetStartPosition() + magnetSplineHeight);
	aMagnetSpline->SetEndPosition(aMagnetSpline->GetEndPosition() + magnetSplineHeight);

	configureCollisionOf(aMagnetSpline);

	aMagnetSpline->SetStartRoll(trackSections[aSplinePointIndex].startRoll);
	aMagnetSpline->SetEndRoll(trackSections[nextSplineIndexOf(aSplinePointIndex)].startRoll);
}

void ATrackGenerator::configureCollisionOf(USplineMeshComponent* aMagnetSpline)
{
	aMagnetSpline->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	aMagnetSpline->SetCollisionResponseToAllChannels(ECR_Ignore);
	aMagnetSpline->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	aMagnetSpline->SetGenerateOverlapEvents(true);
}