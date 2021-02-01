// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"


#if WITH_DEV_AUTOMATION_TESTS


 //Test preparation commands:

DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningAJetAndActivateMixedMotorState);



 //Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckMixedStateActivation, int, tickCount, int, tickLimit, float, previousSpeed, FAutomationTestBase*, test);


#endif //WITH_DEV_AUTOMATION_TESTS
