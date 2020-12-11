// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FSpawnARacePreparationStageCommand, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnARacePreparationMakeItStartCommand);






//Test check commands:


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckLapManagerSpawnedCommand, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckPlayersQuantityOnStartCommand, int, aTickCount, int, aTickLimit, bool, stageHasStarted, FAutomationTestBase*, aTest);





#endif //WITH_DEV_AUTOMATION_TESTS