// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class AJet;
class AJetMOCK;
class AFloorMeshActor;

/**
 * This class is intended to use in tests only and when the editor is playing a PIE session.
 */
class PROJECTR_API PIESessionUtilities
{
private:
	UWorld* pieWorld;
	FActorSpawnParameters spawnParams;
public:
	PIESessionUtilities();
	~PIESessionUtilities();
	UWorld* currentPIEWorld();
	AJet* spawnJetInPIE(FVector atLocation = FVector());
	AJetMOCK* spawnJetMOCKInPIE(FVector atLocation = FVector());
	AFloorMeshActor* spawnFloorMeshActorInPIE(FVector atLocation = FVector());
	AJet* retrieveJetFromPIE();
	AJetMOCK* retrieveJetMOCKFromPIE();
	void processLocalPlayerInputFrom(FName axisMappingName);
};
