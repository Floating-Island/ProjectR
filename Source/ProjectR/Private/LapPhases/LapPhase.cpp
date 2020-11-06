// Fill out your copyright notice in the Description page of Project Settings.


#include "LapPhases/LapPhase.h"

// Sets default values
ALapPhase::ALapPhase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	phaseWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Phase Wall"));

	phaseWallMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Development/Models/phaseWallMesh")));

	phaseWall->SetStaticMesh(phaseWallMesh);

	RootComponent = phaseWall;

	phaseWall->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	phaseWall->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	phaseWall->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	phaseWall->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	phaseWall->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ALapPhase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALapPhase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ALapPhase* ALapPhase::updateState()
{
	return this;
}

