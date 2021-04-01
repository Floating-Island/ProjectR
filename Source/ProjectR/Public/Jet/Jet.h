// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <chrono>

#include "CoreMinimal.h"
#include "DeloreanReplicationMachine.h"
#include "GameFramework/Pawn.h"
#include "Jet.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UAntiGravityComponent;
class USteeringComponent;
class UMotorDriveComponent;
class AMotorStateManager;
class ASteerStateManager;






UCLASS()
class PROJECTR_API AJet : public APawn
{
	GENERATED_BODY()

public:
	AJet();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* physicsMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* jetModelMeshComponent;

	//spring arm component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* springArm;

	//camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* camera;

	//anti-gravity system component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UAntiGravityComponent* antiGravitySystem;

	//steering system component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USteeringComponent* steeringSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		float centerOfMassHeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UMotorDriveComponent* motorDriveSystem;

	UPROPERTY()
		AMotorStateManager* motorManager;

	UPROPERTY()
		ASteerStateManager* steerManager;

	UPROPERTY()
		UDeloreanReplicationMachine* replicationMachine;

	/**With 60 we will have 1000 milliseconds of movements into the past
	 * (assuming 60fps).
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Replication")
		int movementHistorySize;
	
public:
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float currentSpeed();

	float settedTopSpeed();

	void accelerate();

	float acceleration();

	float brakeValue();

	void brake();

	void neutralize();

	bool goesForward();
	bool goesBackwards();

	float steerRadius();
	void steerRight();
	void steerLeft();
	void InReverseInverts(float& aDirection);
	void centerSteer();

	float antiGravityHeight();

	FVector ForwardProjectionOnFloor();

	bool traceToFind(FHitResult& anObstacle);

	FVector forwardVelocity();

	FVector velocityProjectionOnFloor();

	FVector rightVectorProjectionOnFloor();

	bool keyIsPressedFor(const FName anActionMappingName);


//start of replication:
	
	float mass();
	UClass* currentMotorStateClass();
	UClass* currentSteerStateClass();
	float accelerationMagnitudeToAlignVelocityFrom(FVector aCurrentLocation);
	void changesGeneratedByAntiGravityTo(FVector& aLinearAcceleration, FVector& anAngularAcceleration);
	FPhysicsActorHandle& physicsHandleRequestedBy(UDeloreanReplicationMachine* aReplicationMachine);

	void asCurrentMovementSet(FMovementData anotherMovement, UDeloreanReplicationMachine* aRequestingReplicationMachine);
	
	void sendMovementToServerRequestedBy(AMotorStateManager* aMotorManager);
	void sendMovementToServerRequestedBy(ASteerStateManager* aSteerManager);

	float linearDamping();
	float angularDamping();

protected:

	bool needsToReplicateStates;
	
	UFUNCTION(Server, Reliable, WithValidation)
		void serverUpdateMovementWith(FStateData aBunchOfStates);

	FMovementData updatedDataSynchronizedWith(FStateData aBunchOfStates);
	
	UFUNCTION(NetMulticast, Reliable)
		void multicastSynchronizeMovementWith(FMovementData aMovementStructure);

//end of replication
};