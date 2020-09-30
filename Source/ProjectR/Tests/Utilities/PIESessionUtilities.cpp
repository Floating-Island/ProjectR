// Fill out your copyright notice in the Description page of Project Settings.


#include "PIESessionUtilities.h"
#include "../Mocks/JetMOCK.h"
#include "floorMeshActor.h"
#include "Kismet/GameplayStatics.h"

PIESessionUtilities::PIESessionUtilities()
{
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
	UWorld* testWorld = GEditor->GetPIEWorldContext()->World();
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return testWorld->SpawnActor<AJet>(AJet::StaticClass(), atLocation, FRotator(), spawnParams);
}

AJetMOCK* PIESessionUtilities::spawnJetMOCKInPIE(FVector atLocation)
{
	UWorld* testWorld = GEditor->GetPIEWorldContext()->World();
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return testWorld->SpawnActor<AJetMOCK>(AJetMOCK::StaticClass(), atLocation, FRotator(), spawnParams);
}

AFloorMeshActor* PIESessionUtilities::spawnFloorMeshActorInPIE(FVector atLocation)
{
	UWorld* testWorld = GEditor->GetPIEWorldContext()->World();
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return testWorld->SpawnActor<AFloorMeshActor>(AFloorMeshActor::StaticClass(), atLocation, FRotator(), spawnParams);
}

AJet* PIESessionUtilities::retrieveJetFromPIE()
{
	UWorld* testWorld = GEditor->GetPIEWorldContext()->World();
	return Cast<AJet, AActor>(UGameplayStatics::GetActorOfClass(testWorld, AJet::StaticClass()));
}

AJetMOCK* PIESessionUtilities::retrieveJetMOCKFromPIE()
{
	UWorld* testWorld = GEditor->GetPIEWorldContext()->World();
	return Cast<AJetMOCK, AActor>(UGameplayStatics::GetActorOfClass(testWorld, AJetMOCK::StaticClass()));
}
