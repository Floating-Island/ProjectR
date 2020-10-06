// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Track.generated.h"

class UBoxComponent;

UCLASS()
class PROJECTR_API ATrack : public AActor
{
	GENERATED_BODY()

private:
	UFUNCTION()
		void matchMagnetBoxXYExtensionToFloor();
	UFUNCTION()
		void snapMagnetBoxToFloor();
public:
	// Sets default values for this actor's properties
	ATrack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		void magnetizeOverlappingJets();

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* floorComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* magnetBox;

	UPROPERTY(EditDefaultsOnly, Category = "Magnet System")
		float magnetBoxHeight;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void CounterGravityForce(UStaticMeshComponent* actorRootComponent, FVector jetWeightAbsolute);
	void pullTowardsFloor(UStaticMeshComponent* anActorRootComponent, FVector aJetWeightAbsolute);
	void magnetize(UStaticMeshComponent* actorRootComponent, FVector jetWeightAbsolute);
};
