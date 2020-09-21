// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet.h"

#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"

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

	UStaticMesh* Mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Engine/EditorMeshes/EditorCube")));
	meshComponent->SetStaticMesh(Mesh);

	accelerationValue = 500.0f;
	brakeAbsoluteValue = 100.0f;
	topSpeed = 1000.0f;
	steerForceValue = 200.0f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;//this should be changed when we start doing multiplayer. It won't work.
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
	PlayerInputComponent->BindAction("AccelerateAction", IE_Pressed,this,  &AJet::accelerate);
	PlayerInputComponent->BindAction("AccelerateAction", IE_Repeat,this,  &AJet::accelerate);

	PlayerInputComponent->BindAxis("SteerAction",this, &AJet::steer);
}

bool AJet::hasAStaticMesh()
{
	return (meshComponent)? true : false;
}

bool AJet::isMeshTheRootComponent()
{
	return (RootComponent == meshComponent)? true : false;
}

float AJet::currentSpeed()
{
	return meshComponent->GetComponentVelocity().X;
}

float AJet::settedTopSpeed()
{
	return topSpeed;
}

void AJet::accelerate()
{
	if(currentSpeed() < settedTopSpeed() && !FMath::IsNearlyEqual(currentSpeed(), settedTopSpeed(), 0.5f))
	{
		FVector forceToApply = FVector(acceleration(), 0, 0);
		meshComponent->AddForce(forceToApply,NAME_None, true);
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

void AJet::brake()
{
	FVector forceToApply = FVector(-brakeValue(), 0, 0);//notice the '-' next to brakeValue. Brake value's sign is positive.
	meshComponent->AddForce(forceToApply,NAME_None, true);
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

