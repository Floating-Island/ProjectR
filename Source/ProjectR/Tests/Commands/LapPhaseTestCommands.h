// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"

//Test preparation commands:

DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnALapPhaseMOCKInEditorWorldCommand);






//Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckLapPhaseCollisionEnabledCommand, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckLapPhaseCollisionResponseCommand, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckLapPhaseObjectTypeCommand, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckLapPhaseOverlapEventsCommand, FAutomationTestBase*, test);


#endif //WITH_DEV_AUTOMATION_TESTS