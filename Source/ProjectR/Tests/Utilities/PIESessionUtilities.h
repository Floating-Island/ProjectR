// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"


class AJet;
class AJetMOCK;
class AFloorMeshActor;
class ATrackMOCK;
class ATrack;
class ATrackGenerator;
class ATrackManager;
class ATrackManagerMOCK;

/**
 * This class is intended to be used in tests only and when the editor is playing a PIE session.
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
	void processLocalPlayerInputFrom(FName anAxisMappingName);
	

	template <typename anActorDerivedClass>
	anActorDerivedClass* spawnInPIEAnInstanceOf(FVector atLocation = FVector(0));


	template <typename anActorDerivedClass>
	anActorDerivedClass* retrieveFromPIEAnInstanceOf();
};


template <typename anActorDerivedClass>
anActorDerivedClass* PIESessionUtilities::spawnInPIEAnInstanceOf(FVector atLocation)
{
	return pieWorld->SpawnActor<anActorDerivedClass>(anActorDerivedClass::StaticClass(), atLocation, FRotator(0), spawnParams);
}


template <typename anActorDerivedClass>
anActorDerivedClass* PIESessionUtilities::retrieveFromPIEAnInstanceOf()
{
	return Cast<anActorDerivedClass, AActor>(UGameplayStatics::GetActorOfClass(pieWorld, anActorDerivedClass::StaticClass()));
}