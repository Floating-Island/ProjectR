// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class AJet;
class AJetMOCK;
class AFloorMeshActor;
class ATrackMOCK;
class ATrack;
class ATrackGenerator;
class ATrackManager;
class ATrackManagerMOCK;

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
	AJet* spawnJetInPIE(FVector atALocation = FVector(0));
	AJetMOCK* spawnJetMOCKInPIE(FVector atALocation = FVector(0));
	AFloorMeshActor* spawnFloorMeshActorInPIE(FVector atALocation = FVector(0));
	ATrackGenerator* spawnTrackGeneratorInPie(FVector atALocation = FVector(0));
	ATrackManager* spawnTrackManagerInPie(FVector atALocation = FVector(0));
	ATrackManagerMOCK* spawnTrackManagerMOCKInPie(FVector atALocation = FVector(0));
	AJet* retrieveJetFromPIE();
	AJetMOCK* retrieveJetMOCKFromPIE();
	ATrackGenerator* retrieveTrackGeneratorFromPIE();
	ATrackManagerMOCK* retrieveTrackManagerMOCKFromPIE();
	void processLocalPlayerInputFrom(FName anAxisMappingName);

	template <typename anActorDerivedClass>
	anActorDerivedClass* spawnInPIEAnInstanceOf(FVector atLocation = FVector(0));
};


template <typename anActorDerivedClass>
anActorDerivedClass* PIESessionUtilities::spawnInPIEAnInstanceOf(FVector atLocation)
{
	return pieWorld->SpawnActor<anActorDerivedClass>(anActorDerivedClass::StaticClass(), atLocation, FRotator(0), spawnParams);
}
