// Fill out your copyright notice in the Description page of Project Settings.


#include "DeloreanReplicationMachineMOCK.h"

std::deque<FMovementData>& UDeloreanReplicationMachineMOCK::movementHistoryReference()
{
	return movementHistory;
}

void UDeloreanReplicationMachineMOCK::addToHistory(FMovementData aMovement)
{
	addToMovementHistory(aMovement);
}
