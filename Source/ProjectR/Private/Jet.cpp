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

	meshComponent->SetSimulatePhysics(true);
	meshComponent->SetEnableGravity(true);
	meshComponent->SetCanEverAffectNavigation(false);

	UStaticMesh* Mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Engine/EditorMeshes/EditorCube")));
	meshComponent->SetStaticMesh(Mesh);

	accelerationValue = 500.0f;
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
	return meshComponent->GetComponentVelocity().X;
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

bool AJet::hasGravityEnabled()
{
	return meshComponent->IsGravityEnabled();
}

bool AJet::isAffectingNavigation()
{
	return meshComponent->CanEverAffectNavigation();
}

void AJet::accelerate()
{
	FVector forceToApply = FVector(acceleration(), 0, 0);
	meshComponent->AddForce(forceToApply,NAME_None, true);
}

float AJet::acceleration()
{
	return accelerationValue;
}

