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

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float steerTorqueMagnitude;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float steerForceMagnitude;
	
	UFUNCTION()
	void alignVelocityWith(FVector aPreviousForwardVelocity);
	void InReverseInverts(float& aDirectionMultiplier);
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void steer(float aDirectionMultiplier);
	float steerTorque();
	float steerForce();

};
