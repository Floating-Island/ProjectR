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


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnAMotorStateManagerAndNeutralizeIt);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnAMotorStateManagerBrakeAccelerateAndNeutralizeIt);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FServerSpawnMotorStateManager, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FClientAccelerateMotorStateManager, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FClientBrakeMotorStateManager, int, clientQuantity);



//Test check commands:


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMotorStateManagerDefaultState, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMotorStateManagerStateChangesToAccelerating, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMotorStateManagerStateChangesToReversing, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMotorStateManagerStateChangesToNeutral, FAutomationTestBase*, test);


class AMotorState;
DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckMotorStateManagerAccelerateKeepsStateIfAccelerating, int, tickCount, int, tickLimit, AMotorState*, previousState, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckMotorStateManagerBrakeKeepsStateIfReversing, int, tickCount, int, tickLimit, AMotorState*, previousState, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckMotorStateManagerNeutralizeKeepsStateIfNeutral, int, tickCount, int, tickLimit, AMotorState*, previousState, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMotorStateManagerLeavesOneStateInWorld, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckMotorStateManagerServerAndClientAcceleratingState, int, tickCount, int, tickLimit, int, clientQuantity, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckMotorStateManagerServerAndClientReversingState, int, tickCount, int, tickLimit, int, clientQuantity, FAutomationTestBase*, test);




#endif //WITH_DEV_AUTOMATION_TESTS