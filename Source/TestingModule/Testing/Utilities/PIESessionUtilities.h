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
class TESTINGMODULE_API PIESessionUtilities
{
private:
	UWorld* pieWorld;
	FActorSpawnParameters spawnParams;
public:
	PIESessionUtilities();
	~PIESessionUtilities();
	UWorld* defaultPIEWorld();
	UWorld* currentPIEWorld();

	void spawnLocalPlayer();
	void processLocalPlayerInputFrom(FName anAxisMappingName);
	static void processKeyPressFrom(FName anAxisMappingName, APlayerController* aController);
	void processLocalPlayerActionInputFrom(FName anActionMappingName);
	static void processActionKeyPressFrom(FName anActionMappingName, APlayerController* aController);
	void processLocalPlayerActionInputReleaseFrom(FName anActionMappingName);
	static void processActionKeyReleaseFrom(FName anActionMappingName, APlayerController* aController);

	void processEditorClick(FVector2D atCoordinates);

	void processEditorClickAtWindow(FVector2D atCoordinates, TSharedPtr<FGenericWindow> aWindow);


	template <typename anActorDerivedClass>
	anActorDerivedClass* spawnInPIEAnInstanceOf(FVector atLocation = FVector(0));


	template <typename anActorDerivedClass>
	anActorDerivedClass* retrieveFromPIEAnInstanceOf();

	template <typename anActorDerivedClass>
	TArray<anActorDerivedClass*> retrieveFromPIEAllInstancesOf();
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

template <typename anActorDerivedClass>
TArray<anActorDerivedClass*> PIESessionUtilities::retrieveFromPIEAllInstancesOf()
{
	TArray<AActor*> actorsRetrieved = TArray<AActor*>();
	UGameplayStatics::GetAllActorsOfClass(pieWorld, anActorDerivedClass::StaticClass(), actorsRetrieved);

	TArray<anActorDerivedClass*> actorsDerivedFromClassRetrieved = TArray<anActorDerivedClass*>();
	for (const auto& actor : actorsRetrieved)
	{
		anActorDerivedClass* actorFromDerivedClass = Cast<anActorDerivedClass, AActor>(actor);
		if (actorFromDerivedClass)
		{
			actorsDerivedFromClassRetrieved.Add(actorFromDerivedClass);
		}
	}
	return actorsDerivedFromClassRetrieved;
}
