// Fill out your copyright notice in the Description page of Project Settings.


#include "Track.h"
#include "Components/BoxComponent.h"


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
	magnetBox->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
    magnetBox->SetGenerateOverlapEvents(true);

	magnetBox->SetHiddenInGame(true);

	float boxMeshRelativeZLocation = magnetBox->GetUnscaledBoxExtent().Z;
	magnetBox->AddRelativeLocation(FVector(0,0, boxMeshRelativeZLocation));
	/*matchMagnetBoxXYExtensionToFloor();*/
}

//void ATrack::matchMagnetBoxXYExtensionToFloor()
//{
//	magnetBox->GetStaticMesh()->PositiveBoundsExtension.X = floorComponent->GetStaticMesh()->PositiveBoundsExtension.X;
//	magnetBox->GetStaticMesh()->PositiveBoundsExtension.Y = floorComponent->GetStaticMesh()->PositiveBoundsExtension.Y;
//	magnetBox->GetStaticMesh()->NegativeBoundsExtension.X = floorComponent->GetStaticMesh()->NegativeBoundsExtension.X;
//	magnetBox->GetStaticMesh()->NegativeBoundsExtension.X = floorComponent->GetStaticMesh()->NegativeBoundsExtension.X;
//	//(FVector(floorComponent->GetStaticMesh()->GetBounds().BoxExtent.X,floorComponent->GetStaticMesh()->GetBounds().BoxExtent.Y,magnetBox->GetRelativeScale3D().Z));
//}

// Called when the game starts or when spawned
void ATrack::BeginPlay()
{
	Super::BeginPlay();
	/*matchMagnetBoxXYExtensionToFloor();*/
	GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("floor Z bounds: %f."), floorComponent->GetStaticMesh()->GetBoundingBox().GetExtent().Z));
	GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("magnet box Z bounds: %f."), magnetBox->GetUnscaledBoxExtent().Z));
}

// Called every frame
void ATrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

