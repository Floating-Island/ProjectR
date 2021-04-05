// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AntiGravityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTR_API UAntiGravityComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	AActor* owner;
	UPrimitiveComponent* ownerPrimitiveComponent;
public:	
	UAntiGravityComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Anti-Gravity Settings")
		float levitationHeight;
	UPROPERTY(EditAnywhere, Category = "Anti-Gravity Settings")
		float antiGravityForceValue;
	

public:	
	void activateAvoidanceTo(FHitResult anObstacle, FVector aVertexLocation);
	void antiGravityLifting();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float triggerHeight();

	void currentChangesMadeTo(FVector& aLinearAcceleration, FVector& anAngularAcceleration);
};
