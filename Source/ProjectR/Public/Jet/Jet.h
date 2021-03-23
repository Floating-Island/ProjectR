// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <chrono>

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Jet.generated.h"



class USpringArmComponent;
class UCameraComponent;
class UAntiGravityComponent;
class USteeringComponent;
class UMotorDriveComponent;
class AMotorStateManager;
class ASteerStateManager;

UENUM()
enum class EMovementType : uint8 {routine UMETA(DisplayName = "routine"), sendOrReceive UMETA(DisplayName = "sendOrReceive") };

USTRUCT()
struct FMovementData
{
	GENERATED_BODY()

	UPROPERTY()
		int64 timestamp;
	UPROPERTY()
		FVector location;
	UPROPERTY()
		FRotator rotation;
	UPROPERTY()
		FVector linearVelocity;
	UPROPERTY()
		FVector angularVelocityInRadians;
	UPROPERTY()
		UClass* motorStateClass;
	UPROPERTY()
		UClass* steerStateClass;
	UPROPERTY()
		EMovementType type;

	FMovementData()
	{
		timestamp = 0;
		location = FVector(0);
		rotation = FRotator(0);
		linearVelocity = FVector(0);
		angularVelocityInRadians = FVector(0);
		motorStateClass = nullptr;
		steerStateClass = nullptr;
		type = EMovementType::routine;
	}
	
	FMovementData(AActor* actor, EMovementType movementType, UClass* classOfMotorState, UClass* classOfSteerState)
	{
		timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		location = actor->GetActorLocation();
		rotation = actor->GetActorRotation();
		linearVelocity = Cast<UPrimitiveComponent, UActorComponent>(actor->GetRootComponent())->GetPhysicsLinearVelocity();
		angularVelocityInRadians = Cast<UPrimitiveComponent, UActorComponent>(actor->GetRootComponent())->GetPhysicsAngularVelocityInRadians();
		type = movementType;
		motorStateClass = classOfMotorState;
		steerStateClass = classOfSteerState;
	}
};




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

	UPROPERTY(Replicated)
		AMotorStateManager* motorManager;

	UPROPERTY(Replicated)
		ASteerStateManager* steerManager;

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
	void centerSteer();

	float antiGravityHeight();

	FVector ForwardProjectionOnFloor();

	bool traceToFind(FHitResult& anObstacle);

	FVector forwardVelocity();

	FVector velocityProjectionOnFloor();

	FVector rightVectorProjectionOnFloor();

	bool keyIsPressedFor(const FName anActionMappingName);
};