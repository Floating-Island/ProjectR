// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FSpawnARacePreparationStage, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnARacePreparationMakeItStart);






//Test check commands:


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckLapManagerSpawned, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckPlayersQuantityOnStart, int, aTickCount, int, aTickLimit, bool, stageHasStarted, FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckPlayersPossessingJets, int, aTickCount, int, aTickLimit, bool, stageHasStarted, FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckJetsInputDisabled, int, aTickCount, int, aTickLimit, bool, stageHasStarted, FAutomationTestBase*, aTest);





#endif //WITH_DEV_AUTOMATION_TESTS