// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorMeshActor.h"

// Sets default values
AFloorMeshActor::AFloorMeshActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	RootComponent = meshComponent;

	meshComponent->SetSimulatePhysics(false);
	meshComponent->SetEnableGravity(false);
	meshComponent->SetCanEverAffectNavigation(false);

	UStaticMesh* Mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Engine/EditorMeshes/PhAT_FloorBox")));
	meshComponent->SetStaticMesh(Mesh);
}

// Called when the game starts or when spawned
void AFloorMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}


