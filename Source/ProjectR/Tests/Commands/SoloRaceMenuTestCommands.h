// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"


#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:

DEFINE_LATENT_AUTOMATION_COMMAND(FCreateSoloRaceMenu);


//Test check commands:

class USoloRaceMenu;
DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckSoloRaceMenuClickChangesMapCommand, int, aTickCount, int, aTickLimit, USoloRaceMenu*, aRaceMenuInstance,  FAutomationTestBase*, aTest);


#endif //WITH_DEV_AUTOMATION_TESTS
