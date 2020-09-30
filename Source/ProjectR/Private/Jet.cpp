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

	//antiGravitySystem = CreateDefaultSubobject<USceneComponent>(TEXT("AntiGravity System"));
	//antiGravitySystem->SetupAttachment(RootComponent);
	meshComponent->SetMassOverrideInKg(NAME_None, 100, true);
}

// Called when the game starts or when spawned
void AJet::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJet::antiGravityLifting()
{
	FVector traceStart = GetActorLocation();
	float traceLength = 600.0f;//should take consideration of distance from center to actor bounds...
	FVector traceEnd = GetActorLocation() - FVector(0,0,traceLength);

	FHitResult hit;//struct containing hit information
	FCollisionQueryParams collisionParameters;
	collisionParameters.AddIgnoredActor(this);//owner is ignored when tracing
	collisionParameters.bTraceComplex = false;
	collisionParameters.bReturnPhysicalMaterial = false;
	bool hitBlocked = GetWorld()->LineTraceSingleByChannel(hit, traceStart, traceEnd, ECollisionChannel::ECC_Visibility, collisionParameters);

	if(hitBlocked)
	{
		float antiGravityIntensity = hit.Distance / traceLength;
		float antiGravityForceValue = 500000;//should be editable and account for object mass and gravity force.
		float effectiveAntiGravityForceValue = FMath::Lerp(antiGravityForceValue,0.0f,antiGravityIntensity);
		FVector impulse = effectiveAntiGravityForceValue*hit.ImpactNormal;
		meshComponent->AddForce(impulse);
	}
}

// Called every frame
void AJet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	antiGravityLifting();
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

void AJet::accelerate(float anAccelerationMultiplier)
{
	if(currentSpeed() < settedTopSpeed() && !FMath::IsNearlyEqual(currentSpeed(), settedTopSpeed(), 0.5f))
	{
		FVector forceToApply = FVector(acceleration(), 0, 0);
		meshComponent->AddForce(forceToApply*anAccelerationMultiplier,NAME_None, true);
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
	FVector forceToApply = FVector(-brakeValue(), 0, 0);//notice the '-' next to brakeValue. Brake value's sign is positive.
	meshComponent->AddForce(forceToApply*aBrakeMultiplier,NAME_None, true);
}

void AJet::steer(float aDirectionMultiplier)
{
	FVector forceToApply = FVector(0, aDirectionMultiplier*steerForce(), 0);//directionMultiplier is used to steer right or left and to have a range of steering.
	meshComponent->AddForce(forceToApply,NAME_None, true);
}

float AJet::steerForce()
{
	return steerForceValue;
}

