// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
AJet::AJet()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	RootComponent = meshComponent;

	speed = 0.0f;

}

// Called when the game starts or when spawned
void AJet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AJet::currentSpeed()
{
	return speed;
}

void AJet::accelerate()
{
	speed++;
}

void AJet::brake()
{
	speed--;
}

void AJet::setTopSpeed(float aMaximumSpeed)
{
	topSpeed = aMaximumSpeed;
}

float AJet::settedTopSpeed()
{
	return topSpeed;
}

bool AJet::hasAStaticMesh()
{
	return (meshComponent)? true : false;
}

bool AJet::isMeshTheRootComponent()
{
	return (RootComponent == meshComponent)? true : false;
}

