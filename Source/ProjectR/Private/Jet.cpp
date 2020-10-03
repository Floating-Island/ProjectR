// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet.h"

#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "AntiGravityComponent.h"

// Sets default values
AJet::AJet()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	RootComponent = meshComponent;

	meshComponent->SetSimulatePhysics(true);
	meshComponent->SetEnableGravity(true);
	meshComponent->SetCanEverAffectNavigation(false);

	UStaticMesh* Mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Engine/EditorMeshes/ArcadeEditorSphere")));
	meshComponent->SetStaticMesh(Mesh);

	accelerationValue = 5000.0f;
	brakeAbsoluteValue = 1000.0f;
	topSpeed = 1000.0f;
	steerForceValue = 200.0f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;//this should be changed when we start doing multiplayer. It won't work.


	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	springArm->SetupAttachment(RootComponent);
	/*springArm->SetUsingAbsoluteRotation(true);*/

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	camera->SetupAttachment(springArm);

	meshComponent->SetMassOverrideInKg(NAME_None, 100, true);

	antiGravitySystem = CreateDefaultSubobject<UAntiGravityComponent>(TEXT("Anti-Gravity System"));


	
}

// Called when the game starts or when spawned
void AJet::BeginPlay()
{
	Super::BeginPlay();
}



// Called every frame
void AJet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AJet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("AccelerateAction", this, &AJet::accelerate);

	PlayerInputComponent->BindAxis("SteerAction", this, &AJet::steer);

	PlayerInputComponent->BindAxis("BrakeAction", this, &AJet::brake);
}


float AJet::currentSpeed()
{//has to calculate if it's going backwards. Maybe another method that projects onto the forward vector and compares their heading angles...
	return (meshComponent->GetComponentVelocity().ProjectOnTo(GetActorForwardVector())).Size();//speed is calculated as the forward velocity.
}

float AJet::settedTopSpeed()
{
	return topSpeed;
}

void AJet::accelerate(float anAccelerationMultiplier)
{
	if (anAccelerationMultiplier > 0 && currentSpeed() < settedTopSpeed() && !FMath::IsNearlyEqual(currentSpeed(), settedTopSpeed(), 0.5f))
	{
		FVector forceToApply = GetActorForwardVector() * acceleration();
		meshComponent->AddForce(forceToApply * anAccelerationMultiplier, NAME_None, true);
	}
}

float AJet::acceleration()
{
	return accelerationValue;
}

float AJet::brakeValue()
{
	return brakeAbsoluteValue;
}

void AJet::brake(float aBrakeMultiplier)
{
	if (aBrakeMultiplier > 0)
	{
		FVector forceToApply = GetActorForwardVector() * (-brakeValue());//notice the '-' next to brakeValue. Brake value's sign is positive.
		meshComponent->AddForce(forceToApply * aBrakeMultiplier, NAME_None, true);
	}
}

bool AJet::goesForward()
{
	FVector forwardDirection = GetActorForwardVector();
	return GetVelocity().ProjectOnTo(forwardDirection).GetSignVector().Equals(
		forwardDirection.GetSignVector(), 0.1f);
}

bool AJet::goesBackwards()
{
	return !goesForward();
}

void AJet::InReverseInverts(float& aDirectionMultiplier)
{
	if (goesBackwards())//is going backwards
	{
		aDirectionMultiplier = -aDirectionMultiplier;//invert steering
	}
}

void AJet::alignVelocity()
{
	FVector alignedVelocity = GetActorForwardVector().GetSafeNormal() * currentSpeed();
	if (meshComponent->GetComponentVelocity().ProjectOnTo(GetActorForwardVector()).GetSignVector() != GetActorForwardVector().GetSignVector())
	{
		alignedVelocity = (-GetActorForwardVector()).GetSafeNormal() * meshComponent->GetComponentVelocity().Size();///this is used when the jet is in reverse.
		//We should change the direction multiplier so it changes the torque direction when in reverse
	}
	meshComponent->SetPhysicsLinearVelocity(alignedVelocity);//this happens a frame before the torque is applied.
	//velocityAlignmentNeeded = false;//to be able to use this, we need to fire this block on the next tick. Maybe a delegate??
}


//to get drift, the velocity alignment should be disabled by a moment (as long as the drifting lasts), maintaining the acceleration of the jet.
void AJet::steer(float aDirectionMultiplier)
{
	if (aDirectionMultiplier != 0)
	{
		//if reverse, change directionMultiplier sign.
		InReverseInverts(aDirectionMultiplier);
		FVector torqueToApply = FVector(0, 0, aDirectionMultiplier * steerForce());//directionMultiplier is used to steer right or left and to have a range of steering.
		meshComponent->AddTorqueInDegrees(torqueToApply, NAME_None, true);

		GetWorldTimerManager().SetTimerForNextTick(this, &AJet::alignVelocity);//the torque is applied on next tick, so we need to align velocity on next tick also.
	}
}

float AJet::steerForce()
{
	return steerForceValue;
}

