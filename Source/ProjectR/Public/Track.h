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
	ATrack();

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
		void magnetizeOverlappingJets();

	void CounterGravityForce(UStaticMeshComponent* anActorRootComponent, FVector aJetWeightAbsolute);
	void pullTowardsFloor(UStaticMeshComponent* anActorRootComponent, FVector aJetWeightAbsolute);
	void magnetize(UStaticMeshComponent* anActorRootComponent, FVector aJetWeightAbsolute);
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* floorComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* magnetBox;

	UPROPERTY(EditDefaultsOnly, Category = "Magnet System")
		float magnetBoxHeight;

public:
	virtual void Tick(float DeltaTime) override;
	
};
