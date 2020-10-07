// Fill out your copyright notice in the Description page of Project Settings.


#include "Track.h"
#include "Components/BoxComponent.h"
#include "Jet/Jet.h"




ATrack::ATrack()
{
	PrimaryActorTick.bCanEverTick = true;
	floorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor Component"));
	RootComponent = floorComponent;

	UStaticMesh* floorMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Engine/MapTemplates/SM_Template_Map_Floor")));
	floorComponent->SetStaticMesh(floorMesh);

	magnetBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Magnet Box Component"));
	magnetBox->SetupAttachment(RootComponent);
	magnetBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	magnetBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	magnetBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	magnetBox->SetGenerateOverlapEvents(true);

	magnetBox->SetHiddenInGame(true);
	magnetBoxHeight = 400;

	matchMagnetBoxXYExtensionToFloor();

	snapMagnetBoxToFloor();

}

void ATrack::matchMagnetBoxXYExtensionToFloor()
{
	float xExtent = floorComponent->GetStaticMesh()->GetBoundingBox().GetExtent().X;
	float yExtent = floorComponent->GetStaticMesh()->GetBoundingBox().GetExtent().Y;
	magnetBox->SetBoxExtent(FVector(xExtent, yExtent, magnetBoxHeight));
}

void ATrack::snapMagnetBoxToFloor()
{
	float boxMeshRelativeZLocation = magnetBox->GetUnscaledBoxExtent().Z;
	magnetBox->AddRelativeLocation(FVector(0, 0, boxMeshRelativeZLocation));
}

void ATrack::BeginPlay()
{
	Super::BeginPlay();
}

void ATrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	magnetizeOverlappingJets();
}

void ATrack::magnetizeOverlappingJets()
{
	TArray<AActor*> CollectedActors = TArray<AActor*>();
	magnetBox->GetOverlappingActors(CollectedActors, AJet::StaticClass());//get all the actors that overlap with the magnet box.

	for (AActor* actor : CollectedActors)
	{
		AJet* overlappedJet = Cast<AJet, AActor>(actor);
		if (overlappedJet)
		{
			UStaticMeshComponent* actorRootComponent = Cast<UStaticMeshComponent, USceneComponent>(overlappedJet->GetRootComponent());
			if (actorRootComponent && actorRootComponent->IsSimulatingPhysics())
			{
				FVector gravityAccelerationAbsolute = overlappedJet->GetGravityDirection() * GetWorld()->GetGravityZ();
				FVector jetWeightAbsolute = gravityAccelerationAbsolute * actorRootComponent->GetMass();
				magnetize(actorRootComponent, jetWeightAbsolute);
			}
		}
	}
}

void ATrack::magnetize(UStaticMeshComponent* anActorRootComponent, FVector aJetWeightAbsolute)
{
	CounterGravityForce(anActorRootComponent, aJetWeightAbsolute);
	pullTowardsFloor(anActorRootComponent, aJetWeightAbsolute);
}

void ATrack::CounterGravityForce(UStaticMeshComponent* anActorRootComponent, FVector aJetWeightAbsolute)
{
	anActorRootComponent->AddForce(aJetWeightAbsolute);//we counter the weight force....
}

void ATrack::pullTowardsFloor(UStaticMeshComponent* anActorRootComponent, FVector aJetWeightAbsolute)
{
	FVector magnet = -GetActorUpVector() * aJetWeightAbsolute;//notice the '-' we need to pull, so we invert the normal.
	anActorRootComponent->AddForce(magnet);
}