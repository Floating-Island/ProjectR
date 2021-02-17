// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonPIECommands.h"
#include "../Utilities/PIESessionUtilities.h"


bool FSpawnGameModeDefaultPawn::Update()
{
	if(GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();
		AGameModeBase* pieGameMode = sessionUtilities.currentPIEWorld()->GetAuthGameMode();
		APlayerController* pieController = sessionUtilities.currentPIEWorld()->GetFirstPlayerController();

		pieGameMode->SpawnDefaultPawnAtTransform(pieController, FTransform());
		return true;
	}
	return false;
}

bool FSpawnInPIEAnActorOfClass::Update()
 {
	FActorSpawnParameters spawnParameters = FActorSpawnParameters();
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
 	if (GEditor->IsPlayingSessionInEditor() && GEditor->GetPIEWorldContext()->World()->SpawnActor(anActorClass, &actorTransform, spawnParameters))
 	{
 		return true;
 	}
 	return false;
 }

bool FSpawnInEditorAnActorOfClass::Update()
 {
	FActorSpawnParameters spawnParameters = FActorSpawnParameters();
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    if (GEditor->GetEditorWorldContext().World()->GetMapName() == "VoidWorld" && GEditor->GetEditorWorldContext().World()->SpawnActor(anActorClass, &actorTransform, spawnParameters))
	{
		return true;
	}
	return false;
 }


bool FSpawnLocalPlayerInPIE::Update()
{
	if (GEditor->IsPlayingSessionInEditor())
	{
		PIESessionUtilities sessionUtilities = PIESessionUtilities();

		sessionUtilities.spawnLocalPlayer();
		return true;
	}
	return false;
}

