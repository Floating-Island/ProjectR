// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"



/**
* Start a networked PIE session (non simulated)
*/
DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FStartNetworkedPIESession, int32, numParticipants, EPlayNetMode, netMode);