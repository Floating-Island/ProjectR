// // Fill out your copyright notice in the Description page of Project Settings.

 #pragma once

 #include "CoreMinimal.h"
 #include "Misc/AutomationTest.h"

/**
 * This file cointains common latent commands necessary for tests.
 */


 /**
 * Spawn an actor in while in a PIE session.
 */
 DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FSpawnInPIEAnActorOfClass, UClass*, anActorClass, const FTransform, actorTransform);


 /**
 * Spawn an actor in while in editor.
 */
 DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FSpawnInEditorAnActorOfClass, UClass*, anActorClass, const FTransform, actorTransform);


 /**
 * Spawn a local player in while in a PIE session.
 */
DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnLocalPlayerInPIE);
