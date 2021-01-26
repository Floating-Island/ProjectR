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
	USteeringComponent();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
		void alignVelocityFrom(FVector aPreviousForwardVector, FVector aPreviousLocation);
	void InReverseInverts(float& aDirectionMultiplier);

	UPROPERTY(EditAnywhere, Category = "Steering Settings")
		float steerRadius;
	
public:	

	void steer(float aDirectionMultiplier);
	float steeringRadius();

	void steerLeft();
	void steerRight();
};
