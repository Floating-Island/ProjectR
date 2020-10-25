// Fill out your copyright notice in the Description page of Project Settings.


#include "PIESessionUtilities.h"
//to be able to process inputs:
#include "GameFramework/PlayerInput.h"
#include "GameFramework/GameModeBase.h"

PIESessionUtilities::PIESessionUtilities()
{
	if (!GEditor->IsPlayingSessionInEditor())
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

void PIESessionUtilities::processLocalPlayerInputFrom(FName anAxisMappingName)
{
	AGameModeBase* testGameMode = pieWorld->GetAuthGameMode();

	testGameMode->SpawnPlayerFromSimulate(FVector(0), FRotator(0));//spawns a player controller.

	APlayerController* controller = Cast<APlayerController, AActor>(testGameMode->GetGameInstance()->GetFirstLocalPlayerController(pieWorld));

	FName const actionName = anAxisMappingName;
	TArray<FInputAxisKeyMapping> axisMappings = controller->PlayerInput->GetKeysForAxis(actionName);//in the editor, we are going to add a new axis mapping inside Project settings -> Input
	//in the pawn class, we are going to add a player input binding with:
	//	PlayerInputComponent->BindAxis("AxisMappingName",this, &YourPawn::actionToBind);
	//and in the constructor:
	//AutoPossessPlayer = EAutoReceiveInput::Player0;//this should be changed when we start doing multiplayer. It won't work.
	FKey actionKey;
	for (auto axisMap : axisMappings)
	{
		if (axisMap.Scale > 0)
		{
			actionKey = axisMap.Key;
			break;
		}
	}

	controller->InputKey(actionKey, EInputEvent::IE_Repeat, 5.0f, false);
}
