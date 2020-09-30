// Fill out your copyright notice in the Description page of Project Settings.


#include "AntiGravityComponent.h"

// Sets default values for this component's properties
UAntiGravityComponent::UAntiGravityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	owner = GetOwner();
	ownerPrimitiveComponent = Cast<UPrimitiveComponent, UActorComponent>(owner->GetComponentByClass(TSubclassOf<UPrimitiveComponent>()));

	if (!ownerPrimitiveComponent || !ownerPrimitiveComponent->IsSimulatingPhysics())
	{
		throw "Can't use this component on actors that don't have physics enabled nor primitive components!!!";
	}
	levitationHeight = 600.0f;
	antiGravityForceValue = 500000;
	
}


// Called when the game starts
void UAntiGravityComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
}


// Called every frame
void UAntiGravityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	antiGravityLifting();
	// ...
}

void UAntiGravityComponent::activateAntiGravityAlong(float aTraceLength, FHitResult aHit)
{
	float antiGravityIntensity = aHit.Distance / aTraceLength;
	float effectiveAntiGravityForceValue = FMath::Lerp(antiGravityForceValue, 0.0f, antiGravityIntensity);
	FVector impulse = effectiveAntiGravityForceValue * aHit.ImpactNormal;
	ownerPrimitiveComponent->AddForce(impulse, NAME_None, true);
}

void UAntiGravityComponent::antiGravityLifting()
{
	FVector traceStart = owner->GetActorLocation();//should take consideration the actor bounds...
	FVector traceEnd = traceStart - FVector(0, 0, levitationHeight);

	FHitResult hit;
	FCollisionQueryParams collisionParameters;
	collisionParameters.AddIgnoredActor(owner);
	collisionParameters.bTraceComplex = false;
	collisionParameters.bReturnPhysicalMaterial = false;
	bool hitBlocked = owner->GetWorld()->LineTraceSingleByChannel(hit, traceStart, traceEnd, ECollisionChannel::ECC_Visibility, collisionParameters);

	if (hitBlocked)
	{
		activateAntiGravityAlong(levitationHeight, hit);
	}
}

