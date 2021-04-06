// Fill out your copyright notice in the Description page of Project Settings.


#include "LapPhases/LapPhase.h"

// Sets default values
ALapPhase::ALapPhase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	phaseWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Phase Wall"));

	phaseWallMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Development/Models/phaseWallMesh")));

	phaseWall->SetStaticMesh(phaseWallMesh);

	RootComponent = phaseWall;

	phaseWall->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	phaseWall->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	phaseWall->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	phaseWall->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	phaseWall->SetGenerateOverlapEvents(true);
	phaseWall->bHiddenInGame = true;

	allowedDistance = std::numeric_limits<float>::max();
}

// Called when the game starts or when spawned
void ALapPhase::BeginPlay()
{
	Super::BeginPlay();

}

ALapPhase* ALapPhase::updatePhase(ALapPhase* anotherPhase)
{
	return nextPhaseIs(anotherPhase) ? anotherPhase : this;
}

bool ALapPhase::nextPhaseIs(ALapPhase* aPhase)
{
	return false;
}

bool ALapPhase::comesFromInitialLapPhase()
{
	return false;
}

bool ALapPhase::comesFromIntermediateLapPhase()
{
	return false;
}

bool ALapPhase::comesFromFinalLapPhase()
{
	return false;
}

float ALapPhase::maximumAllowedDistance()
{
	return allowedDistance;
}

void ALapPhase::establishDistanceTo(float aNewDistance)
{
	allowedDistance = aNewDistance;
}

