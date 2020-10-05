// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SteeringComponent.generated.h"

class AJet;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTR_API USteeringComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	AJet* owner;
	UPrimitiveComponent* ownerPrimitiveComponent;
	
public:	
	// Sets default values for this component's properties
	USteeringComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float steerForceValue;

	void alignVelocity();
	void InReverseInverts(float& aDirectionMultiplier);
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void steer(float aDirectionMultiplier);
	float steerForce();
};
