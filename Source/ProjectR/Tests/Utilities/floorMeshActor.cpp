// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorMeshActor.h"


AFloorMeshActor::AFloorMeshActor()
{
	PrimaryActorTick.bCanEverTick = false;

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	RootComponent = meshComponent;

	meshComponent->SetSimulatePhysics(false);
	meshComponent->SetEnableGravity(false);
	meshComponent->SetCanEverAffectNavigation(false);

	UStaticMesh* Mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Engine/EditorMeshes/PhAT_FloorBox")));
	meshComponent->SetStaticMesh(Mesh);
}

void AFloorMeshActor::BeginPlay()
{
	Super::BeginPlay();

}


