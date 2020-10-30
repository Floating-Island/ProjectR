// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/SteeringComponent.h"
#include "Jet/Jet.h"


USteeringComponent::USteeringComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	owner = Cast<AJet, AActor>(GetOwner());

	steerTorqueMagnitude = 200;

	steerForceMagnitude = 2000;
}

void USteeringComponent::BeginPlay()
{
	Super::BeginPlay();
	ownerPrimitiveComponent = Cast<UPrimitiveComponent, UActorComponent>(owner->GetComponentByClass(UPrimitiveComponent::StaticClass()));
}

void USteeringComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USteeringComponent::alignVelocityWith(FVector aPreviousForwardVelocity)
{

	FVector currentVelocity = owner->GetVelocity();
	FVector previousForwardVelocityAlignedToCurrentForwardVector = owner->GetActorForwardVector() * aPreviousForwardVelocity.Size();  //owner->GetActorForwardVector() * owner->currentSpeed();
	if (owner->goesBackwards())
	{
		previousForwardVelocityAlignedToCurrentForwardVector = -previousForwardVelocityAlignedToCurrentForwardVector;//velocity should go backwards then...
	}
	UE_LOG(LogTemp, Log, TEXT("Jet speed: %f"), owner->currentSpeed());
	UE_LOG(LogTemp, Log, TEXT("Jet location: %s"), *owner->GetActorLocation().ToString());
	UE_LOG(LogTemp, Log, TEXT("Jet velocity: %s"), *currentVelocity.ToString());
	UE_LOG(LogTemp, Log, TEXT("Jet previous forward velocity: %s"), *aPreviousForwardVelocity.ToString());
	UE_LOG(LogTemp, Log, TEXT("Jet current forward velocity: %s"), *previousForwardVelocityAlignedToCurrentForwardVector.ToString());

	GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("Jet speed: %f"), owner->currentSpeed()));
	GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("Jet location: %s"), *owner->GetActorLocation().ToString()));
	GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("Jet velocity: %s"), *currentVelocity.ToString()));
	GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("Jet previous forward velocity: %s"), *aPreviousForwardVelocity.ToString()));
	GEngine->AddOnScreenDebugMessage(-1, 50.0f, FColor::Green, FString::Printf(TEXT("Jet current forward velocity: %s"), *previousForwardVelocityAlignedToCurrentForwardVector.ToString()));

	ownerPrimitiveComponent->SetPhysicsLinearVelocity(currentVelocity - aPreviousForwardVelocity + previousForwardVelocityAlignedToCurrentForwardVector);//this should happen after the jet steers (gets it's torque applied)
}

void USteeringComponent::InReverseInverts(float& aDirectionMultiplier)
{
	if (owner->goesBackwards())
	{
		aDirectionMultiplier = -aDirectionMultiplier;//invert steering
	}
}

//to get drift, the velocity alignment should be disabled by a moment (as long as the drifting lasts), maintaining the acceleration of the jet.
void USteeringComponent::steer(float aDirectionMultiplier)
{
	if (aDirectionMultiplier != 0 && !FMath::IsNearlyZero(owner->currentSpeed(), 0.5f))
	{
		//if reverse, change directionMultiplier sign.
		InReverseInverts(aDirectionMultiplier);
		FVector torqueToApply = owner->GetActorUpVector() * aDirectionMultiplier * steerTorque();//directionMultiplier is used to steer right or left and to have a range of steering. Should be changed to get the jet normal instead of the Z axis
		ownerPrimitiveComponent->AddTorqueInDegrees(torqueToApply, NAME_None, true);
		float ownerSpeed = owner->currentSpeed();
		ownerPrimitiveComponent->AddForce(owner->GetActorRightVector() * aDirectionMultiplier * steerForceMagnitude, NAME_None, true);
		//float speedAtSteering = owner->currentSpeed();
		//if (speedAtSteering < owner->settedTopSpeed())//to avoid collision problems...
		//{
		//	FVector currentForwardVelocity = owner->GetActorForwardVector() * speedAtSteering;
		//	FTimerDelegate alignVelocityOnNextTick = FTimerDelegate::CreateUObject(this, &USteeringComponent::alignVelocityWith, currentForwardVelocity);
		//	owner->GetWorldTimerManager().SetTimerForNextTick(alignVelocityOnNextTick);//the torque is applied on next tick, so we need to align velocity on next tick also.
		//}

	}
}

float USteeringComponent::steerTorque()
{
	return steerTorqueMagnitude;
}

float USteeringComponent::steerForce()
{
	return steerForceMagnitude;
}

