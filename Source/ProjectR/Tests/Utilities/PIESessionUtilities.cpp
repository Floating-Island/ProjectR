// Fill out your copyright notice in the Description page of Project Settings.


#include "PIESessionUtilities.h"
#include "../Mocks/JetMOCK.h"
#include "floorMeshActor.h"
#include "Kismet/GameplayStatics.h"
//to be able to process inputs:
#include "GameFramework/PlayerInput.h"
#include "GameFramework/GameModeBase.h"

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
	return pieWorld;
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

void PIESessionUtilities::processLocalPlayerInputFrom(FName axisMappingName)
{
	AGameModeBase* testGameMode = pieWorld->GetAuthGameMode();

	testGameMode->SpawnPlayerFromSimulate(FVector(), FRotator());//spawns a player controller.

	
	APlayerController* controller = Cast<APlayerController,AActor>(testGameMode->GetGameInstance()->GetFirstLocalPlayerController(pieWorld));

	FName const actionName = axisMappingName;
	TArray<FInputAxisKeyMapping> axisMappings = controller->PlayerInput->GetKeysForAxis(actionName);//in the editor, we are going to add a new axis mapping inside Project settings -> Input
	//in the jet class, we are going to add a player input binding with:
	//	PlayerInputComponent->BindAxis("AccelerateAction",this, &AJet::accelerate);
	//and in the constructor:
	//AutoPossessPlayer = EAutoReceiveInput::Player0;//this should be changed when we start doing multiplayer. It won't work.
	FKey actionKey;
	for(auto axisMap: axisMappings)
	{
		if(axisMap.Scale > 0)
		{
			actionKey = axisMap.Key;
			break;
		}
	}
	
	controller->InputKey(actionKey,EInputEvent::IE_Repeat,5.0f,false);
}
