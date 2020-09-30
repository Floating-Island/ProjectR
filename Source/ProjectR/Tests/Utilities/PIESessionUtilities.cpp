// Fill out your copyright notice in the Description page of Project Settings.


#include "PIESessionUtilities.h"
#include "../Mocks/JetMOCK.h"
#include "floorMeshActor.h"
#include "Kismet/GameplayStatics.h"

PIESessionUtilities::PIESessionUtilities()
{
	if(!GEditor->IsPlayingSessionInEditor())
	{
		throw "Can't use this class when no PIE session is in progress!!";
	}
	pieWorld = GEditor->GetPIEWorldContext()->World();
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
}

PIESessionUtilities::~PIESessionUtilities()
{
}

UWorld* PIESessionUtilities::currentPIEWorld()
{
	return GEditor->GetPIEWorldContext()->World();
}

AJet* PIESessionUtilities::spawnJetInPIE(FVector atLocation)
{
	return pieWorld->SpawnActor<AJet>(AJet::StaticClass(), atLocation, FRotator(), spawnParams);
}

AJetMOCK* PIESessionUtilities::spawnJetMOCKInPIE(FVector atLocation)
{
	return pieWorld->SpawnActor<AJetMOCK>(AJetMOCK::StaticClass(), atLocation, FRotator(), spawnParams);
}

AFloorMeshActor* PIESessionUtilities::spawnFloorMeshActorInPIE(FVector atLocation)
{
	return pieWorld->SpawnActor<AFloorMeshActor>(AFloorMeshActor::StaticClass(), atLocation, FRotator(), spawnParams);
}

AJet* PIESessionUtilities::retrieveJetFromPIE()
{
	return Cast<AJet, AActor>(UGameplayStatics::GetActorOfClass(pieWorld, AJet::StaticClass()));
}

AJetMOCK* PIESessionUtilities::retrieveJetMOCKFromPIE()
{
	return Cast<AJetMOCK, AActor>(UGameplayStatics::GetActorOfClass(pieWorld, AJetMOCK::StaticClass()));
}
