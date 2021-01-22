// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Jet/MotorStates/MotorState.h"
#include "MotorStateManager.generated.h"

UCLASS()
class PROJECTR_API AMotorStateManager : public AActor
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	AMotorStateManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Replicated);
		AMotorState* motorState;

	UFUNCTION(Server, Reliable, WithValidation)
		void serverAccelerate();

	UFUNCTION(Server, Reliable, WithValidation)
		void serverBrake();

	UFUNCTION(Server, Reliable, WithValidation)
		void serverNeutralize();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	template<class aMotorStateType>
	void updateStateTo();

	void accelerate();
	void brake();
	void neutralize();
};

template <class aMotorStateType>
void AMotorStateManager::updateStateTo()
{
	AMotorState* oldState = motorState;
	FActorSpawnParameters spawnParameters = FActorSpawnParameters();
	spawnParameters.Owner = this;
	motorState = GetWorld()->SpawnActor<aMotorStateType>(spawnParameters);
	oldState->Destroy();
}
