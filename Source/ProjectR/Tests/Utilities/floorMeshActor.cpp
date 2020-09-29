// Fill out your copyright notice in the Description page of Project Settings.


#include "floorMeshActor.h"

// Sets default values
AfloorMeshActor::AfloorMeshActor()
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
void AfloorMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}


