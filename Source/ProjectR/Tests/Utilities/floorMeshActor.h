// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "floorMeshActor.generated.h"

UCLASS()
class PROJECTR_API AfloorMeshActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* meshComponent;
	
public:	
	// Sets default values for this actor's properties
	AfloorMeshActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
