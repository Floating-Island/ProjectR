// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:



//Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckIsSetAsProjectGameInstance, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesMainMenu, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesOneMainMenu, FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesSingleplayerMenu, FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesOneSingleplayerMenu, FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckShowsCursorInMainMenu, FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckShowsCursorInSingleplayerMenu, FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckNecessaryPlayersAreTheExpected, FAutomationTestBase*, aTest);

#endif //WITH_DEV_AUTOMATION_TESTS