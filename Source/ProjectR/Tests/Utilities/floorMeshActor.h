// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorMeshActor.generated.h"

UCLASS()
class PROJECTR_API AFloorMeshActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* meshComponent;
	
public:	
	// Sets default values for this actor's properties
	AFloorMeshActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
