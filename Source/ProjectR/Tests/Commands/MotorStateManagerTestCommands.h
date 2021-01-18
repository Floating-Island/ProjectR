// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnAMotorStateManager);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnAMotorStateManagerAndAccelerateIt);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnAMotorStateManagerAndBrakeIt);



//Test check commands:


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMotorStateManagerDefaultState, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMotorStateManagerStateChangesToAccelerating, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMotorStateManagerStateChangesToReversing, FAutomationTestBase*, test);


#endif //WITH_DEV_AUTOMATION_TESTS