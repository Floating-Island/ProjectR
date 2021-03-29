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


//start of replication machine:
	/** don't add objects directly, use addMovementToHistory instead.*/
	std::deque<FMovementData> movementHistory;

	UFUNCTION()
		void addMovementToHistory();

	/**With 60 we will have 1000 milliseconds of movements into the past
	 * (assuming 60fps).
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Replication")
		int movementHistorySize;

	void addToMovementHistory(FMovementData aMovement);

	FMovementData createMovementHistoryRevisionWith(FMovementData aBaseMovement, FStateData aStatesBase);
	FMovementData createMovementHistoryRevisionWith(FMovementData aBaseMovement, float aTimeDelta);

	void reshapeHistoryFrom(int aMomentInHistory);

	FMovementData simulateNextMovementFrom(FMovementData aPreviousMovement, float simulationDuration = 0);

	FVector retrieveTrackMagnetizationLinearAcceleration();
	
	void asCurrentMovementSet(FMovementData anotherMovement);

private:
	bool generateSendOrReceiveMovementType;

//end of replication machine
	
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



//replication machine:
	FStateData generateCurrentStateDataToSend();

	FMovementData retrieveCurrentMovementDataToSend();

	void synchronizeMovementHistoryWith(FStateData aBunchOfStates);
	void synchronizeMovementHistoryWith(FMovementData aMovementStructure);

//end replication machine


	void sendMovementToServerRequestedBy(UObject* aSubObject);

	
protected:
	UFUNCTION(Server, Reliable, WithValidation)
		void serverUpdateMovementWith(FStateData aBunchOfStates);

	FMovementData updatedDataSynchronizedWith(FStateData aBunchOfStates);
	
	UFUNCTION(NetMulticast, Reliable)
		void multicastSynchronizeMovementWith(FMovementData aMovementStructure);
};