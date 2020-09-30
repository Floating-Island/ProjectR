// Fill out your copyright notice in the Description page of Project Settings.


#include "PIESessionUtilities.h"
#include "../Mocks/JetMOCK.h"

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
	return testWorld->SpawnActor<AJet>(AJet::StaticClass(), atLocation, FRotator(), spawnParams);;
}

AJetMOCK* PIESessionUtilities::spawnJetMOCKInPIE(FVector atLocation)
{
	UWorld* testWorld = GEditor->GetPIEWorldContext()->World();
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	return testWorld->SpawnActor<AJetMOCK>(AJetMOCK::StaticClass(), atLocation, FRotator(), spawnParams);;
}
