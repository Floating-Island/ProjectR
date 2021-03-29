// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Jet/DeloreanReplicationMachine.h"
#include "DeloreanReplicationMachineMOCK.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGMODULE_API UDeloreanReplicationMachineMOCK : public UDeloreanReplicationMachine
{
	GENERATED_BODY()

public:
	std::deque<FMovementData>& movementHistoryReference();
	void addToHistory(FMovementData aMovement);
};
