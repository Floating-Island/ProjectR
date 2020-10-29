// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/Jet.h"

#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Jet/AntiGravityComponent.h"
#include "Jet/SteeringComponent.h"


AJet::AJet()
{
	PrimaryActorTick.bCanEverTick = true;
	bGenerateOverlapEventsDuringLevelStreaming = true;
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	RootComponent = meshComponent;

	meshComponent->SetSimulatePhysics(true);
	meshComponent->SetEnableGravity(true);
	meshComponent->SetCanEverAffectNavigation(false);

	UStaticMesh* Mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Development/Models/jetMesh")));
	meshComponent->SetStaticMesh(Mesh);

	accelerationValue = 5000.0f;
	brakeAbsoluteValue = 1000.0f;
	topSpeed = 1000.0f;	

	AutoPossessPlayer = EAutoReceiveInput::Player0;//this should be changed when we start doing multiplayer. It won't work.


	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	springArm->SetupAttachment(RootComponent);
	/*springArm->SetUsingAbsoluteRotation(true);*/

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	camera->SetupAttachment(springArm);

	meshComponent->SetMassOverrideInKg(NAME_None, 100, true);

	antiGravitySystem = CreateDefaultSubobject<UAntiGravityComponent>(TEXT("Anti-Gravity System"));

	steeringSystem = CreateDefaultSubobject<USteeringComponent>(TEXT("Steering System"));

    meshComponent->SetGenerateOverlapEvents(true);
	meshComponent->SetCollisionObjectType(ECC_Pawn);

	centerOfMassHeight = -100;
	meshComponent->SetCenterOfMass(FVector(0,0, centerOfMassHeight));
}

void AJet::BeginPlay()
{
	Super::BeginPlay();
}

void AJet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("AccelerateAction", this, &AJet::accelerate);

	PlayerInputComponent->BindAxis("SteerAction", this, &AJet::steer);

	PlayerInputComponent->BindAxis("BrakeAction", this, &AJet::brake);
}


float AJet::currentSpeed()
{
	return (meshComponent->GetComponentVelocity().ProjectOnTo(GetActorForwardVector())).Size();//speed is calculated as the forward velocity
}

float AJet::settedTopSpeed()
{
	return topSpeed;
}

void AJet::accelerate(float anAccelerationMultiplier)
{
	if (anAccelerationMultiplier > 0 && currentSpeed() < settedTopSpeed() && !FMath::IsNearlyEqual(currentSpeed(), settedTopSpeed(), 1.0f))
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

float AJet::steerForce()
{
	return steeringSystem->steerForce();
}

void AJet::steer(float aDirectionMultiplier)
{
	steeringSystem->steer(aDirectionMultiplier);
}
