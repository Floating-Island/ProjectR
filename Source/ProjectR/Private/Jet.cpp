// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet.h"

#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

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
	steerForceValue = 2000.0f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;//this should be changed when we start doing multiplayer. It won't work.


	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	springArm->SetupAttachment(RootComponent);
	springArm->SetUsingAbsoluteRotation(true);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	camera->SetupAttachment(springArm);
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

	PlayerInputComponent->BindAxis("AccelerateAction",this, &AJet::accelerate);

	PlayerInputComponent->BindAxis("SteerAction",this, &AJet::steer);

	PlayerInputComponent->BindAxis("BrakeAction",this, &AJet::brake);
}


float AJet::currentSpeed()
{
	return meshComponent->GetComponentVelocity().X;
}

float AJet::settedTopSpeed()
{
	return topSpeed;
}

void AJet::accelerate(float accelerationMultiplier)
{
	if(currentSpeed() < settedTopSpeed() && !FMath::IsNearlyEqual(currentSpeed(), settedTopSpeed(), 0.5f))
	{
		FVector forceToApply = FVector(acceleration(), 0, 0);
		meshComponent->AddForce(forceToApply*accelerationMultiplier,NAME_None, true);
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

void AJet::brake(float brakeMultiplier)
{
	FVector forceToApply = FVector(-brakeValue(), 0, 0);//notice the '-' next to brakeValue. Brake value's sign is positive.
	meshComponent->AddForce(forceToApply*brakeMultiplier,NAME_None, true);
}

void AJet::steer(float directionMultiplier)
{
	FVector forceToApply = FVector(0, directionMultiplier*steerForce(), 0);//directionMultiplier is used to steer right or left and to have a range of steering.
	meshComponent->AddForce(forceToApply,NAME_None, true);
}

float AJet::steerForce()
{
	return steerForceValue;
}

