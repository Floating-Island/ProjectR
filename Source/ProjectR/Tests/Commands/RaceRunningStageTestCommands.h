// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnARaceRunningCallNextStageCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnARaceRunningCommand);




//Test check commands:


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckEndedStageSpawnedCommand, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckEndedStageSpawnedWithNoRunningJetsCommand, FAutomationTestBase*, test);




#endif //WITH_DEV_AUTOMATION_TESTS