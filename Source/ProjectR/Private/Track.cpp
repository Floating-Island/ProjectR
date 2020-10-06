// Fill out your copyright notice in the Description page of Project Settings.


#include "Track.h"
#include "Components/BoxComponent.h"
#include "Jet/Jet.h"



// Sets default values
ATrack::ATrack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

// Called when the game starts or when spawned
void ATrack::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ATrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	magnetizeOverlappingJets();
}

void ATrack::magnetizeOverlappingJets()
{
	TArray<AActor*> CollectedActors = TArray<AActor*>();
	magnetBox->GetOverlappingActors(CollectedActors, AJet::StaticClass());//get all the actors that overlap with the magnet box.
	GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("heyy")));
	for (AActor* actor : CollectedActors)
	{
		AJet* overlappedJet = Cast<AJet, AActor>(actor);
		if (overlappedJet)
		{
			UStaticMeshComponent* actorRootComponent = Cast<UStaticMeshComponent, USceneComponent>(overlappedJet->GetRootComponent());
			if (actorRootComponent && actorRootComponent->IsSimulatingPhysics())
			{
				FVector gravity = overlappedJet->GetGravityDirection() * GetWorld()->GetDefaultGravityZ();
				actorRootComponent->AddForce(-gravity);//we counter gravity....
				FVector magnet = -GetActorUpVector() * gravity.Size();//notice the '-' we need to pull, so we invert the normal.
				GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("magnet vector: %s."), *magnet.ToString()));
				actorRootComponent->AddForce(magnet * 10);
			}
		}
	}
}