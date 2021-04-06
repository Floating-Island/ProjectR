// Fill out your copyright notice in the Description page of Project Settings.


#include "Jet/Jet.h"



#include "Kismet/GameplayStatics.h"
#include "../../Public/Track/TrackManager.h"
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

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	physicsMeshComponent->SetGenerateOverlapEvents(true);
	physicsMeshComponent->SetCollisionObjectType(ECC_Pawn);

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	springArm->SetupAttachment(RootComponent);
	/*springArm->SetUsingAbsoluteRotation(true);*/

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	camera->SetupAttachment(springArm);

	antiGravitySystem = CreateDefaultSubobject<UAntiGravityComponent>(TEXT("Anti-Gravity System"));

	steeringSystem = CreateDefaultSubobject<USteeringComponent>(TEXT("Steering System"));

	motorDriveSystem = CreateDefaultSubobject<UMotorDriveComponent>(TEXT("Motor Drive System"));

	SetReplicates(true);
	SetReplicateMovement(false);
	needsToReplicateStates = false;
	motorManager = nullptr;
	steerManager = nullptr;

	physicsMeshComponent->SetVisibility(false, true);

	jetModelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(*FString("Jet Model Mesh Component"));
	
	jetModelMeshComponent->SetupAttachment(physicsMeshComponent);

	movementHistorySize = 60;
	replicationMachine = CreateDefaultSubobject<UDeloreanReplicationMachine>(UDeloreanReplicationMachine::StaticClass()->GetFName());

	bAlwaysRelevant = true;
}

void AJet::PostLoad()
{
	Super::PostLoad();

	physicsMeshComponent->SetMassOverrideInKg(NAME_None, 100, true);
	
	centerOfMassHeight = -100;
	physicsMeshComponent->SetCenterOfMass(FVector(0, 0, centerOfMassHeight));

	jetModelMeshComponent->SetMassOverrideInKg(NAME_None, 0, true);
}

void AJet::BeginPlay()
{
	Super::BeginPlay();
}

void AJet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	motorManager->activate(motorDriveSystem);
	steerManager->activate(steeringSystem);
	replicationMachine->addMovementToHistory();

	if(needsToReplicateStates)
	{
		needsToReplicateStates = false;
		serverUpdateMovementWith(replicationMachine->generateCurrentStateDataToSend());
	}
}

void AJet::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FActorSpawnParameters spawnParameters = FActorSpawnParameters();
	spawnParameters.Owner = this;
	
	motorManager = GetWorld()->SpawnActor<AMotorStateManager>(spawnParameters);
	steerManager = GetWorld()->SpawnActor<ASteerStateManager>(spawnParameters);
	replicationMachine->setDefaultVariablesTo(this, movementHistorySize);
}

void AJet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("AccelerateAction", EInputEvent::IE_Pressed, this, &AJet::accelerate);
	PlayerInputComponent->BindAction("AccelerateAction", EInputEvent::IE_Released, this, &AJet::neutralize);

	PlayerInputComponent->BindAction("SteerRightAction", EInputEvent::IE_Pressed, this, &AJet::steerRight);
	PlayerInputComponent->BindAction("SteerRightAction", EInputEvent::IE_Released, this, &AJet::centerSteer);

	PlayerInputComponent->BindAction("SteerLeftAction", EInputEvent::IE_Pressed, this, &AJet::steerLeft);
	PlayerInputComponent->BindAction("SteerLeftAction", EInputEvent::IE_Released, this, &AJet::centerSteer);


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
	if(keyIsPressedFor(FName("BrakeAction")))
	{
		motorManager->mix();
		return;
	}
	motorManager->accelerate();
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
	if(keyIsPressedFor(FName("AccelerateAction")))
	{
		motorManager->mix();
		return;
	}
	motorManager->brake();
}

void AJet::neutralize()
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
	if(keyIsPressedFor(FName("SteerLeftAction")))
	{
		steerManager->center();
		return;
	}
	steerManager->steerRight();
}

void AJet::steerLeft()
{
	if(keyIsPressedFor(FName("SteerRightAction")))
	{
		steerManager->center();
		return;
	}
	steerManager->steerLeft();
}

void AJet::InReverseInverts(float& aDirection)
{
	if (goesBackwards())
	{
		aDirection = -aDirection;//invert direction
	}
}

void AJet::centerSteer()
{
	if(keyIsPressedFor(FName("SteerLeftAction")))
	{
		steerManager->steerLeft();
		return;
	}

	if(keyIsPressedFor(FName("SteerRightAction")))
	{
		steerManager->steerRight();
		return;
	}
	steerManager->center();
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
		return FVector::VectorPlaneProject(physicsMeshComponent->GetForwardVector(), obstacle.Normal);
	}
	return GetActorForwardVector();
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
	return FVector::VectorPlaneProject(GetVelocity(), physicsMeshComponent->GetUpVector());
}

FVector AJet::rightVectorProjectionOnFloor()
{
	FHitResult obstacle;
	bool nearFloor = traceToFind(obstacle);

	if (nearFloor)
	{
		return FVector::VectorPlaneProject(physicsMeshComponent->GetRightVector(), obstacle.Normal);
	}
	return physicsMeshComponent->GetRightVector();
}

bool AJet::traceToFind(FHitResult& anObstacle)
{
	FVector jetLocation = physicsMeshComponent->GetComponentLocation();//should take consideration the actor bounds...
	float rayExtension = 1000;
	FVector rayEnd = -(physicsMeshComponent->GetUpVector()) * rayExtension;

	FCollisionQueryParams collisionParameters;
	collisionParameters.AddIgnoredActor(this);
	collisionParameters.bTraceComplex = false;
	collisionParameters.bReturnPhysicalMaterial = false;

	return  GetWorld()->LineTraceSingleByChannel(anObstacle, jetLocation, rayEnd, ECollisionChannel::ECC_Visibility, collisionParameters);
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

float AJet::mass()
{
	return physicsMeshComponent->GetMass();
}

UClass* AJet::currentMotorStateClass()
{
	return motorManager->stateClass();
}

UClass* AJet::currentSteerStateClass()
{
	return steerManager->stateClass();
}

float AJet::accelerationMagnitudeToAlignVelocityFrom(FVector aCurrentLocation)
{
	return steeringSystem->accelerationMagnitudeToAlignVelocityFrom(aCurrentLocation);
}

void AJet::changesGeneratedByAntiGravityTo(FVector& aLinearAcceleration, FVector& anAngularAcceleration)
{
	antiGravitySystem->currentChangesMadeTo(aLinearAcceleration, anAngularAcceleration);
}

FVector AJet::retrieveTrackMagnetizationLinearAcceleration()
{
	ATrackManager* trackManager = Cast<ATrackManager, AActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ATrackManager::StaticClass()));
	if(trackManager == nullptr)
	{
		return FVector(0, 0, - FMath::Abs(GetWorld()->GetGravityZ()));
	}
	return trackManager->pullingAccelerationTo(this);
}

FPhysicsActorHandle& AJet::physicsHandleRequestedBy(UDeloreanReplicationMachine* aReplicationMachine)
{
	if(aReplicationMachine != replicationMachine)
	{
		throw "attempting to get hold of the physics actor handle of a jet when the replication machine that called it isn't the one stored in the jet";
	}
	return physicsMeshComponent->BodyInstance.GetPhysicsActorHandle();
}

void AJet::asCurrentMovementSet(FMovementData anotherMovement, UDeloreanReplicationMachine* aRequestingReplicationMachine)
{
	if(aRequestingReplicationMachine == replicationMachine)
	{
		SetActorLocation(anotherMovement.location);
		SetActorRotation(anotherMovement.rotation);
		physicsMeshComponent->SetPhysicsAngularVelocityInRadians(anotherMovement.angularVelocityInRadians);
		physicsMeshComponent->SetPhysicsLinearVelocity(anotherMovement.linearVelocity);
		motorManager->overrideStateTo(anotherMovement.timestampedStates.motorStateClass, this);
		steerManager->overrideStateTo(anotherMovement.timestampedStates.steerStateClass, this);
	}
}

void AJet::sendMovementToServerRequestedBy(AMotorStateManager* aMotorManager)
{
	if(aMotorManager == motorManager)
	{
		needsToReplicateStates = true;
	}
}

void AJet::sendMovementToServerRequestedBy(ASteerStateManager* aSteerManager)
{
	if(aSteerManager == steerManager)
	{
		needsToReplicateStates = true;
	}
}

float AJet::linearDamping()
{
	return physicsMeshComponent->GetLinearDamping();
}

float AJet::angularDamping()
{
	return physicsMeshComponent->GetAngularDamping();
}

void AJet::serverUpdateMovementWith_Implementation(FStateData aBunchOfStates)
{
	FMovementData movementForClient = updatedDataSynchronizedWith(aBunchOfStates);
	if(replicationMachine->hasDataForClient())
	{
		multicastSynchronizeMovementWith(movementForClient);
	}
}

bool AJet::serverUpdateMovementWith_Validate(FStateData aBunchOfStates)
{
	return true;
}

FMovementData AJet::updatedDataSynchronizedWith(FStateData aBunchOfStates)
{
	replicationMachine->synchronizeMovementHistoryWith(aBunchOfStates);
	return replicationMachine->retrieveCurrentMovementDataToSend();
}

void AJet::multicastSynchronizeMovementWith_Implementation(FMovementData aMovementStructure)
{
	replicationMachine->synchronizeMovementHistoryWith(aMovementStructure);
}

