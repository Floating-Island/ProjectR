// Fill out your copyright notice in the Description page of Project Settings.


#include "Track/TrackGenerator.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Track/TrackManager.h"
#include "Kismet/GameplayStatics.h"

ATrackGenerator::ATrackGenerator()
{
	bGenerateOverlapEventsDuringLevelStreaming = true;
	splineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	RootComponent = splineComponent;

	defaultRoadMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Development/Models/roadFloor")));

	splineComponent->SetClosedLoop(true, true);

	magnetSplineHeightDistanceToRoadSpline = 400.0f;

	defaultMagnetMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Development/Models/roadFloor")));

	trackSections = TArray<FTrackSectionData>();

	collisionsEnabled = true;
}




// Called when the game starts or when spawned
void ATrackGenerator::BeginPlay()
{
	Super::BeginPlay();
	collisionsEnabled = true;
	recreateSplineMeshComponents();
	
	trackManagerSubscription();//should always be after the spline mesh components are recreated.
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
			trackSections.Last().roadMesh = defaultRoadMesh;
			trackSections.Last().magnetMesh = defaultMagnetMesh;
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

	editorCollisionsEnabled(aRoadSpline);

	aRoadSpline->Mobility = RootComponent->Mobility;

	aRoadSpline->SetStaticMesh(trackSections[aSplinePointIndex].roadMesh);

	aRoadSpline->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	configureRollAndWidthOf(aRoadSpline, aSplinePointIndex);
}

void ATrackGenerator::configureComponentPositionsAndTangents(int32 aSplinePointIndex, USplineMeshComponent* aSplineMesh)
{
	FVector currentSplinePointPosition = splineComponent->GetLocationAtSplinePoint(aSplinePointIndex, ESplineCoordinateSpace::Local);
	FVector nextSplinePointPosition = splineComponent->GetLocationAtSplinePoint(nextSplineIndexOf(aSplinePointIndex), ESplineCoordinateSpace::Local);
	FVector currentSplinePointTangent = splineComponent->GetTangentAtSplinePoint(aSplinePointIndex, ESplineCoordinateSpace::Local);
	FVector nextSplinePointTangent = splineComponent->GetTangentAtSplinePoint(nextSplineIndexOf(aSplinePointIndex), ESplineCoordinateSpace::Local);

	aSplineMesh->SetStartAndEnd(currentSplinePointPosition, currentSplinePointTangent, nextSplinePointPosition, nextSplinePointTangent);
}

void ATrackGenerator::editorCollisionsEnabled(USplineMeshComponent* aSplineMeshComponent)
{
	if(!collisionsEnabled)
	{
		aSplineMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ATrackGenerator::configureRollAndWidthOf(USplineMeshComponent* aSplineMeshComponent, int32 AtASplinePointIndex)
{
	aSplineMeshComponent->SetStartRoll(trackSections[AtASplinePointIndex].startRoll);
	aSplineMeshComponent->SetEndRoll(trackSections[nextSplineIndexOf(AtASplinePointIndex)].startRoll);

	float thickness = 1;
	aSplineMeshComponent->SetStartScale(FVector2D(trackSections[AtASplinePointIndex].initialWidth, thickness));
	aSplineMeshComponent->SetEndScale(FVector2D(trackSections[nextSplineIndexOf(AtASplinePointIndex)].initialWidth, thickness));
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

	aMagnetSpline->SetStartPosition(aMagnetSpline->GetStartPosition() + magnetSplineHeight);//won't be necessary when I create a static mesh for magnet splines...
	aMagnetSpline->SetEndPosition(aMagnetSpline->GetEndPosition() + magnetSplineHeight);//won't be necessary when I create a static mesh for magnet splines...

	configureCollisionOf(aMagnetSpline);

	configureRollAndWidthOf(aMagnetSpline, aSplinePointIndex);
}

void ATrackGenerator::configureCollisionOf(USplineMeshComponent* aMagnetSpline)
{
	aMagnetSpline->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	aMagnetSpline->SetCollisionResponseToAllChannels(ECR_Ignore);
	aMagnetSpline->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	aMagnetSpline->SetGenerateOverlapEvents(true);
	editorCollisionsEnabled(aMagnetSpline);
}

void ATrackGenerator::trackManagerSubscription()
{
	ATrackManager* worldTrackManager = Cast<ATrackManager,AActor>(UGameplayStatics::GetActorOfClass(GetWorld(),ATrackManager::StaticClass()));
	if(worldTrackManager)
	{
		worldTrackManager->addGeneratorAndSubscribe(this);
	}
	else
	{
		GetWorld()->SpawnActor(ATrackManager::StaticClass());
	}
}


void ATrackGenerator::toMagnetOverlapSubscribe(ATrackManager* aManager)
{
	for (auto& trackSection : trackSections)
	{
		trackSection.magnetSpline->OnComponentBeginOverlap.AddDynamic(aManager, &ATrackManager::addJetToMagnetize);
	}
}

float ATrackGenerator::distanceAlongSplineOf(AActor* anActor)
{
	FVector actorLocation = anActor->GetActorLocation();
	float locationInputKey = splineComponent->FindInputKeyClosestToWorldLocation(actorLocation);
	float segmentEndParameter = locationInputKey / splineComponent->GetNumberOfSplinePoints();//so it's a value between 0 and 1, the duration of the spline (parametrized curve).

    float distanceAlongSpline = splineComponent->SplineCurves.GetSegmentLength(0, segmentEndParameter);//it gets the length from 0 to t in the parametrized curve.
    //zero represents the start of the spline.
    //if you need to calculate distance treating the spline as a closed loop, use:
    //splineComponent->SplineCurves.GetSegmentLength(0, segmentEndParameter, true);

    return distanceAlongSpline;
}

float ATrackGenerator::length()
{
	return splineComponent->GetSplineLength();
}

FVector ATrackGenerator::rightVectorAt(float aDistanceAlongSpline)
{
	return splineComponent->GetRightVectorAtDistanceAlongSpline(aDistanceAlongSpline, ESplineCoordinateSpace::World);
}

FVector ATrackGenerator::locationAt(float aDistanceAlongSpline)
{
	return splineComponent->GetLocationAtDistanceAlongSpline(aDistanceAlongSpline);
}
