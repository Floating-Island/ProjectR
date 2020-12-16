// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:

DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningATrackGenerator);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningARotatedTrackGeneratorAndJetCloseToIt);





//Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckATrackManagerTrackGenerators, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckATrackManagerStoresJetsWhenOverlap, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckATrackManagerAttractsJets, int, aTickCount, int, aTickLimit, float, aPreviousDistance, FAutomationTestBase*, test);




#endif //WITH_DEV_AUTOMATION_TESTS