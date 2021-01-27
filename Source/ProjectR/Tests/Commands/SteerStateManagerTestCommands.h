// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:

DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnASteerStateManagerMOCK);


DEFINE_LATENT_AUTOMATION_COMMAND(FLeftSteerASteerStateManagerMOCK);


DEFINE_LATENT_AUTOMATION_COMMAND(FRightSteerASteerStateManagerMOCK);


//Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckSteerStateManagerCurrentState, UClass*, expectedState, FString, message, int, tickCount, int, tickLimit, FAutomationTestBase*, test);

#endif //WITH_DEV_AUTOMATION_TESTS