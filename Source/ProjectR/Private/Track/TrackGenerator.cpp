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
	splineMeshes = TArray<USplineMeshComponent*>();

	roadMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Content/Development/Models/roadFloor")));

	magnetBoxes = TArray<USplineMeshComponent*>();

	splineComponent->SetClosedLoop(true, true);

	magnetBoxHeightDistanceToSplineMesh = 400.0f;

	magnetBoxMesh = roadMesh;
}

// Called when the game starts or when spawned
void ATrackGenerator::BeginPlay()
{
	Super::BeginPlay();
	for (auto splineMesh : splineMeshes)
	{
		splineMesh->DestroyComponent();
	}
	for (auto magnetBox : magnetBoxes)
	{
		magnetBox->DestroyComponent();
	}
	updateSplineMeshes();
	UE_LOG(LogTemp, Log, TEXT("Started playing."));
	UE_LOG(LogTemp, Log, TEXT("Spline Mesh quantity at begin play: %d."),magnetBoxes.Num());
	UE_LOG(LogTemp, Log, TEXT("Magnet box quantity at begin play: %d."),magnetBoxes.Num());
	UE_LOG(LogTemp, Log, TEXT("Quantity of components at begin play: %d."),GetComponents().Num());
	UE_LOG(LogTemp, Log, TEXT("Quantity of spline points at begin play: %d."),splineComponent->GetNumberOfSplinePoints());
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

void ATrackGenerator::toMagnetOverlapSubscribe(ATrackManager* aManager)
{
	UE_LOG(LogTemp, Log, TEXT("starting subscription."));
	UE_LOG(LogTemp, Log, TEXT("Magnet box quantity: %d."),magnetBoxes.Num());
	for (auto magnetMesh : magnetBoxes)
	{
		magnetMesh->OnComponentBeginOverlap.AddDynamic(aManager, &ATrackManager::addJetToMagnetize);
		UE_LOG(LogTemp, Log, TEXT("subscribing track manager."));
	}
}

FVector ATrackGenerator::closestLocationTo(FVector anotherLocation)
{
	return splineComponent->FindLocationClosestToWorldLocation(anotherLocation, ESplineCoordinateSpace::World);
}

void ATrackGenerator::updateSplineMeshes()
{
	splineMeshes.Empty();
	magnetBoxes.Empty();
	int32 splineQuantity = splineComponent->GetNumberOfSplinePoints();
	for (int32 splinePointIndex = 0; splinePointIndex < splineQuantity; ++splinePointIndex)
	{
		USplineMeshComponent* splineMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(), FName(TEXT("Spline Mesh Component "), splinePointIndex));
		configureSplineMesh(splinePointIndex, splineMesh);

		USplineMeshComponent* magnetBox = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass(), FName(TEXT("Magnet Box Component "), splinePointIndex));
		configureMagnetBox(splinePointIndex, splineMesh, magnetBox);
	}
}

void ATrackGenerator::configureSplineMesh(int32 aSplinePointIndex, USplineMeshComponent* aSplineMesh)
{
	aSplineMesh->RegisterComponent();
	splineMeshes.Add(aSplineMesh);

	aSplineMesh->bSmoothInterpRollScale = true;

	configureComponentPositionsAndTangents(aSplinePointIndex, aSplineMesh);



	aSplineMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	aSplineMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	aSplineMesh->Mobility = RootComponent->Mobility;
	aSplineMesh->SetStaticMesh(roadMesh);
	aSplineMesh->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
}

void ATrackGenerator::configureComponentPositionsAndTangents(int32 aSplinePointIndex, USplineMeshComponent* aSplineMesh)
{
	FVector currentSplinePointPosition = splineComponent->GetLocationAtSplinePoint(aSplinePointIndex, ESplineCoordinateSpace::Local);
	FVector nextSplinePointPosition = splineComponent->GetLocationAtSplinePoint(nextSplineIndex(aSplinePointIndex), ESplineCoordinateSpace::Local);
	FVector currentSplinePointTangent = splineComponent->GetTangentAtSplinePoint(aSplinePointIndex, ESplineCoordinateSpace::Local);
	FVector nextSplinePointTangent = splineComponent->GetTangentAtSplinePoint(nextSplineIndex(aSplinePointIndex), ESplineCoordinateSpace::Local);

	aSplineMesh->SetStartAndEnd(currentSplinePointPosition, currentSplinePointTangent, nextSplinePointPosition, nextSplinePointTangent);
}

void ATrackGenerator::configureMagnetBox(int32 aSplinePointIndex, USplineMeshComponent* aSplineMesh, USplineMeshComponent* aMagnetBox)
{
	aMagnetBox->RegisterComponent();
	UE_LOG(LogTemp, Log, TEXT("Magnet box quantity before adding another one: %d."),magnetBoxes.Num());
	UE_LOG(LogTemp, Log, TEXT("Adding magnet box."));
	magnetBoxes.Add(aMagnetBox);
	UE_LOG(LogTemp, Log, TEXT("Magnet box quantity after adding another one: %d."),magnetBoxes.Num());
	aMagnetBox->Mobility = aSplineMesh->Mobility;

	aMagnetBox->SetHiddenInGame(true);

	aMagnetBox->bSmoothInterpRollScale = true;

	configureComponentPositionsAndTangents(aSplinePointIndex, aMagnetBox);

	aMagnetBox->SetStaticMesh(magnetBoxMesh);

	//aMagnetBox->SetStartScale(aMagnetBox->GetStartScale()*5);//should be removed once the initial bounds Z extension is known (of a mesh created for it)...
	//aMagnetBox->SetEndScale(aMagnetBox->GetEndScale()*5);//should be removed once the initial bounds Z extension is known (of a mesh created for it)...

	aMagnetBox->AttachToComponent(aSplineMesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	FVector magnetBoxHeight = FVector(0, 0, magnetBoxHeightDistanceToSplineMesh);

	aMagnetBox->SetStartPosition(aMagnetBox->GetStartPosition() + magnetBoxHeight);
	aMagnetBox->SetEndPosition(aMagnetBox->GetEndPosition() + magnetBoxHeight);

	configureCollisionOf(aMagnetBox);
}

void ATrackGenerator::configureCollisionOf(USplineMeshComponent* aMagnetBox)
{
	aMagnetBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	aMagnetBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	aMagnetBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	aMagnetBox->SetGenerateOverlapEvents(true);
}