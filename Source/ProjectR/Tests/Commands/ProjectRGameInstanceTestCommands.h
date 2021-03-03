// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

class FSimplePIETestBase;



//Test preparation commands:



//Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckIsSetAsProjectGameInstance, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesMainMenu, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesOneMainMenu, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesSingleplayerMenu, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesOneSingleplayerMenu, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckShowsCursorInMainMenu, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckShowsCursorInSingleplayerMenu, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesSplitscreenMenu, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesOneSplitscreenMenu, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckShowsCursorInSplitscreenMenu, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckLoadMainMenuSetsExpectedPlayersToOne, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSessionManagerSetInGameInstance, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesLANMultiplayerMenu, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesOneLANMultiplayerMenu, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckShowsCursorInLanMultiplayerMenu, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesLobbyMenu, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesOneLobbyMenu, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckLoadLobbyMenuShowsMouseCursor, FSimplePIETestBase*, test);

#endif //WITH_DEV_AUTOMATION_TESTS