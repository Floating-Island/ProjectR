// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"

/**
 * This file cointains common latent commands necessary for networked tests.
 */

/**
* Start a networked PIE session (non simulated)
*/
DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FStartNetworkedPIESession, int32, numParticipants, EPlayNetMode, netMode);


/**
* Spawn an actor in server while in a networked PIE session (non simulated).
* It also looks for the client controller and makes it the actor's owner.
*/
DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FServerSpawnActorOfClass, UClass*, anActorClass, FTransform, actorTransform, int, clientQuantity);


/**
* Spawn a pawn in server while in a networked PIE session (non simulated).
* It also looks for the client controller, makes it the pawn's owner and possess it. 
*/
DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FServerSpawnPawnOfClass, UClass*, aPawnClass, FTransform, pawnTransform, int, clientQuantity);