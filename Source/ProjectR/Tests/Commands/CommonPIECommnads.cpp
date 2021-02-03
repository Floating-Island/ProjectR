// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonPIECommands.h"

bool FSpawnActorOfClass::Update()
 {
	FActorSpawnParameters spawnParameters = FActorSpawnParameters());
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
 	if (GEditor->IsPlayingSessionInEditor() && GEditor->GetPIEWorldContext()->World()->SpawnActor(anActorClass, &actorTransform, spawnParameters))
 	{
 		return true;
 	}
 	return false;
 }
