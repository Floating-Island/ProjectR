// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/AntiGravityComponent.h"


UAntiGravityComponent::UAntiGravityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	levitationHeight = 600.0f;
	antiGravityForceValue = 5000;
	owner = GetOwner();
}

void UAntiGravityComponent::BeginPlay()
{
	Super::BeginPlay();
	ownerPrimitiveComponent = Cast<UPrimitiveComponent, UActorComponent>(owner->GetComponentByClass(UPrimitiveComponent::StaticClass()));

}

void UAntiGravityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	antiGravityLifting();
}

float UAntiGravityComponent::triggerHeight()
{
	return levitationHeight;
}

void UAntiGravityComponent::activateAvoidanceTo(FHitResult anObstacle, FVector aVertexLocation)
{
	float antiGravityIntensity = anObstacle.Distance / levitationHeight;
	float effectiveAntiGravityForceValue = FMath::Lerp(antiGravityForceValue, 0.0f, antiGravityIntensity);
	FVector impulse = effectiveAntiGravityForceValue * anObstacle.ImpactNormal * ownerPrimitiveComponent->GetMass();//added mass, add force at location takes mass into account so we have to counter it.
	//ownerPrimitiveComponent->AddForce(impulse, NAME_None, true);
	ownerPrimitiveComponent->AddForceAtLocation(impulse, aVertexLocation);
}

void UAntiGravityComponent::antiGravityLifting()
{
	TArray<FName> vertexSockets = ownerPrimitiveComponent->GetAllSocketNames();
	TArray<FVector> socketLocations = TArray<FVector>();
	for (const auto& socket : vertexSockets)
	{
		if (!socket.IsEqual(FName("BackSteeringPoint")) && !socket.IsEqual(FName("FrontSteeringPoint")))
		{
			socketLocations.Add(ownerPrimitiveComponent->GetSocketLocation(socket));
		}
	}
	FVector ownerLowerBound = owner->GetActorLocation();//should take consideration the actor bounds...
	FVector antiGravityExtensionLimit = ownerLowerBound - owner->GetActorUpVector() * triggerHeight();//should use the up vector of the actor and extend it downwards. (if its sideways, current implementation doesn't work).
	FHitResult obstacle;
	FCollisionQueryParams collisionParameters;
	collisionParameters.AddIgnoredActor(owner);
	collisionParameters.bTraceComplex = false;
	collisionParameters.bReturnPhysicalMaterial = false;

	for (const auto& socketLocation : socketLocations)
	{
		bool inAntiGravityRange = owner->GetWorld()->LineTraceSingleByChannel(obstacle, socketLocation, antiGravityExtensionLimit, ECollisionChannel::ECC_Visibility, collisionParameters);

		if (inAntiGravityRange)
		{
			activateAvoidanceTo(obstacle, socketLocation);
		}
	}
}

