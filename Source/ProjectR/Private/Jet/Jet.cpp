// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/Jet.h"


#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Jet/AntiGravityComponent.h"
#include "Jet/SteeringComponent.h"
#include "Jet/MotorDriveComponent.h"
#include "Jet/MotorStates/MotorStateManager.h"
#include "Jet/SteerStates/SteerStateManager.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/PlayerController.h"



AJet::AJet()
{
	PrimaryActorTick.bCanEverTick = true;
	bGenerateOverlapEventsDuringLevelStreaming = true;
	physicsMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Physics Mesh Component"));
	RootComponent = physicsMeshComponent;

	physicsMeshComponent->SetSimulatePhysics(true);
	physicsMeshComponent->SetEnableGravity(true);
	physicsMeshComponent->SetCanEverAffectNavigation(false);

	UStaticMesh* physicsMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, TEXT("/Game/Development/Models/jetMesh")));
	physicsMeshComponent->SetStaticMesh(physicsMesh);

	physicsMeshComponent->SetMassOverrideInKg(NAME_None, 100, true);

	physicsMeshComponent->SetGenerateOverlapEvents(true);
	physicsMeshComponent->SetCollisionObjectType(ECC_Pawn);

	centerOfMassHeight = -100;
	physicsMeshComponent->SetCenterOfMass(FVector(0, 0, centerOfMassHeight));

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	springArm->SetupAttachment(RootComponent);
	/*springArm->SetUsingAbsoluteRotation(true);*/

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	camera->SetupAttachment(springArm);

	antiGravitySystem = CreateDefaultSubobject<UAntiGravityComponent>(TEXT("Anti-Gravity System"));

	steeringSystem = CreateDefaultSubobject<USteeringComponent>(TEXT("Steering System"));

	motorDriveSystem = CreateDefaultSubobject<UMotorDriveComponent>(TEXT("Motor Drive System"));

	SetReplicates(true);
	SetReplicateMovement(true);
	motorManager = nullptr;
	steerManager = nullptr;
}

void AJet::BeginPlay()
{
	Super::BeginPlay();

}

void AJet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(IsValid(motorManager))
	{
		motorManager->activate(motorDriveSystem);
	}
	if(IsValid(steerManager))
	{
		steerManager->activate(steeringSystem);
	}
}

void AJet::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if(HasAuthority())
	{
		FActorSpawnParameters spawnParameters = FActorSpawnParameters();
		spawnParameters.Owner = this;
		
		motorManager = GetWorld()->SpawnActor<AMotorStateManager>(spawnParameters);
		steerManager = GetWorld()->SpawnActor<ASteerStateManager>(spawnParameters);
	}
}

void AJet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("AccelerateAction", EInputEvent::IE_Pressed, this, &AJet::accelerate);
	PlayerInputComponent->BindAction("AccelerateAction", EInputEvent::IE_Released, this, &AJet::neutralize);

	PlayerInputComponent->BindAction("SteerRightAction", EInputEvent::IE_Pressed, this, &AJet::steerRight);

	PlayerInputComponent->BindAction("SteerLeftAction", EInputEvent::IE_Pressed, this, &AJet::steerLeft);


	PlayerInputComponent->BindAction("BrakeAction", EInputEvent::IE_Pressed, this, &AJet::brake);
	PlayerInputComponent->BindAction("BrakeAction", EInputEvent::IE_Released, this, &AJet::neutralize);
}


float AJet::currentSpeed()
{
	return motorDriveSystem->currentSpeed();
}

float AJet::settedTopSpeed()
{
	return motorDriveSystem->settedTopSpeed();
}

void AJet::accelerate()
{
	if(IsValid(motorManager))
	{
		if(keyIsPressedFor(FName("BrakeAction")))
		{
			motorManager->mix();
			return;
		}
		motorManager->accelerate();
	}
}

float AJet::acceleration()
{
	return motorDriveSystem->acceleration();
}

float AJet::brakeValue()
{
	return motorDriveSystem->brakeValue();
}

void AJet::brake()
{
	if(IsValid(motorManager))
	{
		if(keyIsPressedFor(FName("AccelerateAction")))
		{
			motorManager->mix();
			return;
		}
		motorManager->brake();
	}
}

void AJet::neutralize()
{
	if(IsValid(motorManager))
	{
		if(keyIsPressedFor(FName("BrakeAction")))
		{
			motorManager->brake();
			return;
		}

		if(keyIsPressedFor(FName("AccelerateAction")))
		{
			motorManager->accelerate();
			return;
		}
		motorManager->neutralize();
	}
}

bool AJet::goesForward()
{
	return motorDriveSystem->goesForward();
}

bool AJet::goesBackwards()
{
	return motorDriveSystem->goesBackwards();
}

float AJet::steerRadius()
{
	return steeringSystem->steeringRadius();
}

void AJet::steerRight()
{
	if(IsValid(steerManager))
	{
		steerManager->steerRight();
	}
}

void AJet::steerLeft()
{
	if(IsValid(steerManager))
	{
		steerManager->steerLeft();
	}
}

float AJet::antiGravityHeight()
{
	return antiGravitySystem->triggerHeight();
}

FVector AJet::ForwardProjectionOnFloor()
{
	FHitResult obstacle;
	bool nearFloor = traceToFind(obstacle);

	if (nearFloor)
	{
		return FVector::VectorPlaneProject(GetActorForwardVector(), obstacle.Normal);
	}
	else
	{
		return GetActorForwardVector();
	}
}

bool AJet::traceToFind(FHitResult& obstacle)
{
	FVector jetLocation = GetActorLocation();//should take consideration the actor bounds...
	float rayExtension = 1000;
	FVector rayEnd = -GetActorUpVector() * rayExtension;

	FCollisionQueryParams collisionParameters;
	collisionParameters.AddIgnoredActor(this);
	collisionParameters.bTraceComplex = false;
	collisionParameters.bReturnPhysicalMaterial = false;

	return  GetWorld()->LineTraceSingleByChannel(obstacle, jetLocation, rayEnd, ECollisionChannel::ECC_Visibility, collisionParameters);
}

FVector AJet::forwardVelocity()
{
	return GetVelocity().ProjectOnTo(ForwardProjectionOnFloor());
}

FVector AJet::velocityProjectionOnFloor()
{
	FHitResult obstacle;
	bool nearFloor = traceToFind(obstacle);

	if (nearFloor)
	{
		return FVector::VectorPlaneProject(GetVelocity(), obstacle.Normal);
	}
	else
	{
		return FVector::VectorPlaneProject(GetVelocity(), GetActorUpVector());
	}
}

FVector AJet::rightVectorProjectionOnFloor()
{
	FHitResult obstacle;
	bool nearFloor = traceToFind(obstacle);

	if (nearFloor)
	{
		return FVector::VectorPlaneProject(GetActorRightVector(), obstacle.Normal);
	}
	else
	{
		return GetActorRightVector();
	}
}

bool AJet::keyIsPressedFor(const FName anActionMappingName)
{
	APlayerController* controller = Cast<APlayerController, AController>(GetController());
	if(controller)
	{
		TArray<FInputActionKeyMapping> actionMappings = controller->PlayerInput->GetKeysForAction(anActionMappingName);
		for (auto actionMapping : actionMappings)
		{
			if(controller->IsInputKeyDown(actionMapping.Key.GetFName()))
			{
				return true;
			}
		}
	}
	return false;
}

void AJet::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AJet, motorManager);
	DOREPLIFETIME(AJet, steerManager);
}