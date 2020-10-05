// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/AntiGravityComponent.h"

// Sets default values for this component's properties
UAntiGravityComponent::UAntiGravityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	levitationHeight = 600.0f;
	antiGravityForceValue = 5000;
	owner = GetOwner();
}


// Called when the game starts
void UAntiGravityComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	ownerPrimitiveComponent = Cast<UPrimitiveComponent, UActorComponent>(owner->GetComponentByClass(UPrimitiveComponent::StaticClass()));

}


// Called every frame
void UAntiGravityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	antiGravityLifting();
	// ...
}

void UAntiGravityComponent::activateAvoidanceTo(FHitResult anObstacle)
{
	float antiGravityIntensity = anObstacle.Distance / levitationHeight;
	float effectiveAntiGravityForceValue = FMath::Lerp(antiGravityForceValue, 0.0f, antiGravityIntensity);
	FVector impulse = effectiveAntiGravityForceValue * anObstacle.ImpactNormal;
	ownerPrimitiveComponent->AddForce(impulse, NAME_None, true);
}

void UAntiGravityComponent::antiGravityLifting()
{
	FVector ownerLowerBound = owner->GetActorLocation();//should take consideration the actor bounds...
	FVector antiGravityExtensionLimit = ownerLowerBound - FVector(0, 0, levitationHeight);
	FHitResult obstacle;
	FCollisionQueryParams collisionParameters;
	collisionParameters.AddIgnoredActor(owner);
	collisionParameters.bTraceComplex = false;
	collisionParameters.bReturnPhysicalMaterial = false;
	bool inAntiGravityRange = owner->GetWorld()->LineTraceSingleByChannel(obstacle, ownerLowerBound, antiGravityExtensionLimit, ECollisionChannel::ECC_Visibility, collisionParameters);

	if (inAntiGravityRange)
	{
		activateAvoidanceTo(obstacle);
	}
}
