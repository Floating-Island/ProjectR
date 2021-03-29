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

#include "extensions/PxRigidBodyExt.h"
#include "PhysXPublic.h"
#include "Jet/SteerStates/CenterSteerState.h"
#include "Track/TrackManager.h"
#include "Kismet/GameplayStatics.h"




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

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
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
	SetReplicateMovement(false);
	motorManager = nullptr;
	steerManager = nullptr;

	physicsMeshComponent->SetVisibility(false, true);

	jetModelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(*FString("Jet Model Mesh Component"));
	
	jetModelMeshComponent->SetupAttachment(physicsMeshComponent);

	jetModelMeshComponent->SetMassOverrideInKg(NAME_None, 0);

	movementHistorySize = 60;
	
}

void AJet::BeginPlay()
{
	Super::BeginPlay();
	movementHistory = std::deque<FMovementData>(movementHistorySize, FMovementData());
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
	addMovementToHistory();
}

void AJet::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	FActorSpawnParameters spawnParameters = FActorSpawnParameters();
	spawnParameters.Owner = this;
	
	motorManager = GetWorld()->SpawnActor<AMotorStateManager>(spawnParameters);
	steerManager = GetWorld()->SpawnActor<ASteerStateManager>(spawnParameters);
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
		if(keyIsPressedFor(FName("SteerLeftAction")))
		{
			steerManager->center();
			return;
		}
		steerManager->steerRight();
	}
}

void AJet::steerLeft()
{
	if(IsValid(steerManager))
	{
		if(keyIsPressedFor(FName("SteerRightAction")))
		{
			steerManager->center();
			return;
		}
		steerManager->steerLeft();
	}
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
	if(IsValid(steerManager))
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

bool AJet::traceToFind(FHitResult& anObstacle)
{
	FVector jetLocation = GetActorLocation();//should take consideration the actor bounds...
	float rayExtension = 1000;
	FVector rayEnd = -GetActorUpVector() * rayExtension;

	FCollisionQueryParams collisionParameters;
	collisionParameters.AddIgnoredActor(this);
	collisionParameters.bTraceComplex = false;
	collisionParameters.bReturnPhysicalMaterial = false;

	return  GetWorld()->LineTraceSingleByChannel(anObstacle, jetLocation, rayEnd, ECollisionChannel::ECC_Visibility, collisionParameters);
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




void AJet::addMovementToHistory()
{
	if(IsValid(motorManager) && IsValid(steerManager))
	{
		addToMovementHistory(FMovementData(this, 
			generateSendOrReceiveMovementType? EMovementType::sendOrReceive : EMovementType::routine, 
			motorManager->stateClass(), 
			steerManager->stateClass()));
		generateSendOrReceiveMovementType = false;
	}
}

void AJet::addToMovementHistory(FMovementData aMovement)
{
	movementHistory.push_front(aMovement);
	movementHistory.pop_back();
}

FStateData AJet::generateCurrentStateDataToSend()
{
	FStateData currentStates = FStateData(motorManager->stateClass(), steerManager->stateClass());

	generateSendOrReceiveMovementType = true;
	
	return currentStates;
}

FMovementData AJet::retrieveCurrentMovementDataToSend()
{
	generateSendOrReceiveMovementType = true;
	return FMovementData(this, EMovementType::sendOrReceive, motorManager->stateClass(), steerManager->stateClass());
}

void AJet::synchronizeMovementHistoryWith(FStateData aBunchOfStates)
{
	//never change timestamps!!!
	//go back into the movement history and find the movement previous to the states timestamp.
	//using that movement location, rotation and velocities, calculate the next movement with the states of aBunchOfStates
	//take the next move (the one that would come after the states timestamp), set the aBunchOfStates as the movement states.
	//Set the movement as the one calculated.
	//
	//Start the loop (from the move that follows until the current movement in history):
	//if the movement type is SendOrReceive, keep the states as is.
	//if the movement type is routine (but only before the first SendOrReceive of the loop), overwrite the states with the ones on the previous movement.
	////(you could use a boolean to check if you can overwrite)
	//calculate the current movement using the current states and the movement of the previous move.
	//set the current movement in the structure.
	//advance to next movement.

	UE_LOG(LogTemp, Log, TEXT("\n\n ******** Starting Server synchronization ******** \n\n"));
	UE_LOG(LogTemp, Log, TEXT("\n\n ****** Current Move: ****** \n %s \n\n"), *movementHistory[0].ToString());
	
	int historyMoment = 0;
	if(aBunchOfStates.timestamp < movementHistory[0].timestampedStates.timestamp)//check that the states don't come from the future...
	{
		while (historyMoment < movementHistory.size())
		{
			if(movementHistory[historyMoment].timestampedStates.timestamp <= aBunchOfStates.timestamp)//we found the moment previous to the received states...
			{
				break;
			}
			++historyMoment;
		}
	}
	if(historyMoment != movementHistory.size())
	{
		FMovementData historyRevisionStart = createMovementHistoryRevisionWith(movementHistory[historyMoment], aBunchOfStates);
		--historyMoment;//historyMoment is previous to --historyMoment
		if(historyMoment >=0)
		{
			movementHistory[historyMoment].regenerateMoveFrom(historyRevisionStart, historyRevisionStart.type);
			reshapeHistoryFrom(historyMoment);//chain reaction of history rewrite
		}
	}
	UE_LOG(LogTemp, Log, TEXT("\n\n ******** Server synchronization Finalized ******** \n\n"));
}

void AJet::synchronizeMovementHistoryWith(FMovementData aMovementStructure)
{
	//never change timestamps!!!
	//go back into the movement history and find the movement following (in time) the movement structure parameter.
	//calculate the time delta (in milliseconds) and transform it to seconds.
	//Calculate the movement that would be made on that time delta utilizing the movement structure parameter.
	//Set the calculated movement structure (including its states) as the movement following it.
	//
	//Start the loop (from the move that follows until the current movement in history):
	//if the movement type is SendOrReceive, keep the states as is.
	//if the movement type is routine (but only before the first SendOrReceive of the loop), overwrite the states with the ones on the previous movement.
	////(you could use a boolean to check if you can overwrite)
	//calculate the current movement using the current states and the movement of the previous move.
	//set the current movement in the structure.
	//advance to next movement.

	UE_LOG(LogTemp, Log, TEXT("\n\n ******** Starting Client synchronization ******** \n\n"));
	UE_LOG(LogTemp, Log, TEXT("\n\n ****** Current Move: ****** \n %s \n\n"), *movementHistory[0].ToString());
	
	int historyMoment = 0;
	if(aMovementStructure.timestampedStates.timestamp < movementHistory[0].timestampedStates.timestamp)//check that the movement don't come from the future...
	{
		while (historyMoment < movementHistory.size())
		{
			if(movementHistory[historyMoment].timestampedStates.timestamp <= aMovementStructure.timestampedStates.timestamp)//we found the moment previous to the received movement...
			{
				break;
			}
			++historyMoment;
		}
	}
	if(historyMoment != movementHistory.size())
	{
		--historyMoment;//go to a more recent movement...
		if(historyMoment >=0)
		{
			float timeBetweenMovements = (movementHistory[historyMoment].timestampedStates.timestamp - aMovementStructure.timestampedStates.timestamp) / 1000.0f;
			FMovementData historyRevisionStart = createMovementHistoryRevisionWith(aMovementStructure, timeBetweenMovements);
			movementHistory[historyMoment].regenerateMoveFrom(historyRevisionStart, historyRevisionStart.type);
			reshapeHistoryFrom(historyMoment);//chain reaction of history rewrite
		}
	}
	UE_LOG(LogTemp, Log, TEXT("\n\n ******** Client synchronization Finalized ******** \n\n"));
}

FMovementData AJet::createMovementHistoryRevisionWith(FMovementData aBaseMovement, FStateData aStatesBase)
{
	aBaseMovement.timestampedStates.motorStateClass = aStatesBase.motorStateClass;
	aBaseMovement.timestampedStates.steerStateClass = aStatesBase.steerStateClass;

	FMovementData revisedMovement = FMovementData();

	revisedMovement = simulateNextMovementFrom(aBaseMovement);//calculate next movement with these values...

	return revisedMovement;
}

FMovementData AJet::createMovementHistoryRevisionWith(FMovementData aBaseMovement, float aTimeDelta)
{
	FMovementData revisedMovement = FMovementData();

	revisedMovement = simulateNextMovementFrom(aBaseMovement, aTimeDelta);//calculate next movement with these values using the time delta instead of the tick delta time...

	return revisedMovement;
}

void AJet::reshapeHistoryFrom(int aMomentInHistory)
{
	bool needsToChangeStates = true;

	FVector steerCounterAcceleration = FVector(0);
	FVector steerAlignAcceleration = FVector(0);
	bool needsToAlign = false;
	while(aMomentInHistory > 0)
	{
		FMovementData currentMovementInHistory = movementHistory[aMomentInHistory];
		FMovementData nextMovementInHistory = movementHistory[aMomentInHistory - 1];
		if(needsToChangeStates && nextMovementInHistory.type != EMovementType::sendOrReceive)
		{
			nextMovementInHistory.timestampedStates.motorStateClass = currentMovementInHistory.timestampedStates.motorStateClass;
			nextMovementInHistory.timestampedStates.steerStateClass = currentMovementInHistory.timestampedStates.steerStateClass;
		}
		else //found the first movement in history that was already sent or received from the server...
		{
			needsToChangeStates = false;
		}
		FStateData nextMovementStates = nextMovementInHistory.timestampedStates;

		FMovementData rewrittenNextMovement = FMovementData();

		rewrittenNextMovement = simulateNextMovementFrom(currentMovementInHistory);//calculate rewritten next movement with these values... 


		
		nextMovementInHistory.regenerateMoveFrom(rewrittenNextMovement, nextMovementInHistory.type);
		nextMovementInHistory.timestampedStates = nextMovementStates;

		//align velocity!!! only if left or right steering == not center steering...
		if(needsToAlign)
		{
			UE_LOG(LogTemp, Log, TEXT("\n aligning velocity \n"));
			needsToAlign = false;
			float timeBetweenMovements = (nextMovementInHistory.timestampedStates.timestamp - currentMovementInHistory.timestampedStates.timestamp) / 1000.0f;
			nextMovementInHistory.linearVelocity += (steerCounterAcceleration + steerAlignAcceleration) * timeBetweenMovements;
			nextMovementInHistory.location = currentMovementInHistory.location + nextMovementInHistory.linearVelocity * timeBetweenMovements;
		}
		
		if(currentMovementInHistory.timestampedStates.steerStateClass != UCenterSteerState::StaticClass())
		{
			UE_LOG(LogTemp, Log, TEXT("\n needs to align velocity \n"));
			needsToAlign = true;
			asCurrentMovementSet(currentMovementInHistory);
			FVector currentForwardProjection = ForwardProjectionOnFloor();
			FVector currentLocation = GetActorLocation();
			asCurrentMovementSet(nextMovementInHistory);
			float alignmentAcceleration =  steeringSystem->accelerationMagnitudeToAlignVelocityFrom(currentLocation);
			steerCounterAcceleration = (-currentForwardProjection) * alignmentAcceleration;
			steerAlignAcceleration = ForwardProjectionOnFloor() * alignmentAcceleration;
		}
		--aMomentInHistory;
	}
	asCurrentMovementSet(movementHistory[0]);
}

FMovementData AJet::simulateNextMovementFrom(FMovementData aPreviousMovement, float simulationDuration)
{
	
	asCurrentMovementSet(aPreviousMovement);

	FVector sumOfAngularAccelerations = FVector(0);
	sumOfAngularAccelerations += antiGravitySystem->currentTotalAngularAccelerationMade();
	sumOfAngularAccelerations += Cast<USteerState, UObject>(aPreviousMovement.timestampedStates.steerStateClass->ClassDefaultObject)->angularAccelerationGeneratedTo(this);

	FVector sumOfLinearAccelerations = FVector(0);
	sumOfLinearAccelerations += Cast<UMotorState, UObject>(aPreviousMovement.timestampedStates.motorStateClass->ClassDefaultObject)->linearAccelerationsGeneratedTo(this);
	sumOfLinearAccelerations += retrieveTrackMagnetizationLinearAcceleration();

	if(simulationDuration == 0)
	{
		simulationDuration = GetWorld()->GetDeltaSeconds();
	}

	FVector netForceApplied = sumOfLinearAccelerations * physicsMeshComponent->GetMass();
	FVector netTorqueApplied = sumOfAngularAccelerations * physicsMeshComponent->GetMass();

	PxVec3 linearVelocityDelta = PxVec3();
	PxVec3 angularVelocityDelta = PxVec3();

	PxRigidBody* body = FPhysicsInterface_PhysX::GetPxRigidBody_AssumesLocked(physicsMeshComponent->BodyInstance.GetPhysicsActorHandle());

	PxRigidBodyExt::computeVelocityDeltaFromImpulse(*body, 
		U2PVector(netForceApplied) * simulationDuration, 
		U2PVector(netTorqueApplied) * simulationDuration, 
		linearVelocityDelta, 
		angularVelocityDelta
	);

	FMovementData simulatedMove = aPreviousMovement;

	simulatedMove.linearVelocity += P2UVector(linearVelocityDelta);
	
	simulatedMove.location += simulatedMove.linearVelocity * simulationDuration;
	
	simulatedMove.angularVelocityInRadians += FVector::DegreesToRadians(P2UVector(angularVelocityDelta));

	FVector angularRotation = simulatedMove.angularVelocityInRadians * simulationDuration;
	
	FQuat angularVelocityQuaternion = FQuat(angularRotation.GetSafeNormal(), angularRotation.Size());

	simulatedMove.rotation =  ( angularVelocityQuaternion * simulatedMove.rotation.Quaternion() ).Rotator();

	UE_LOG(LogTemp, Log, TEXT("\n simulated movement: \n %s \n"), *simulatedMove.ToString());
	UE_LOG(LogTemp, Log, TEXT(">>angular velocity delta: %s"), *P2UVector(angularVelocityDelta).ToString());
	UE_LOG(LogTemp, Log, TEXT(">>angular velocity delta 'in radians': %s\n"), *FVector::DegreesToRadians(P2UVector(angularVelocityDelta)).ToString());
	
	return simulatedMove;
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

void AJet::asCurrentMovementSet(FMovementData anotherMovement)
{
	SetActorLocation(anotherMovement.location);
	SetActorRotation(anotherMovement.rotation);
	physicsMeshComponent->SetPhysicsAngularVelocityInRadians(anotherMovement.angularVelocityInRadians);
	physicsMeshComponent->SetPhysicsLinearVelocity(anotherMovement.linearVelocity);
	motorManager->overrideStateTo(anotherMovement.timestampedStates.motorStateClass, this);
	steerManager->overrideStateTo(anotherMovement.timestampedStates.steerStateClass, this);
}






void AJet::sendMovementToServerRequestedBy(UObject* aSubObject)
{
	/*if(Cast<AJet, UObject>(aSubObject->GetTypedOuter(AJet::StaticClass())) == this)
	{*/
		serverUpdateMovementWith(generateCurrentStateDataToSend());
	//}
}

void AJet::serverUpdateMovementWith_Implementation(FStateData aBunchOfStates)
{
	multicastSynchronizeMovementWith(updatedDataSynchronizedWith(aBunchOfStates));
}

bool AJet::serverUpdateMovementWith_Validate(FStateData aBunchOfStates)
{
	return true;
}

void AJet::multicastSynchronizeMovementWith_Implementation(FMovementData aMovementStructure)
{
	synchronizeMovementHistoryWith(aMovementStructure);
}


FMovementData AJet::updatedDataSynchronizedWith(FStateData aBunchOfStates)
{
	synchronizeMovementHistoryWith(aBunchOfStates);
	return retrieveCurrentMovementDataToSend();
}
