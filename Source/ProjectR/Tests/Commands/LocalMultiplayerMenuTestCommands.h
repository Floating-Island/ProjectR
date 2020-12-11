// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:



//Test check commands:


class ULocalMultiplayerMenu;
DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckLocalMultiplayerMenuClickGoBackRemovesFromViewportCommand, int, aTickCount, int, aTickLimit, ULocalMultiplayerMenu*, aLocalMultiplayerMenuInstance, bool, isMenuInstanciated, FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckLocalMultiplayerMenuClickGoBackBringsMainMenuCommand, int, aTickCount, int, aTickLimit, ULocalMultiplayerMenu*, aLocalMultiplayerMenuInstance, bool, isMenuInstanciated, FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckLocalMultiplayerMenuClickPlaySetsPlayers, int, aTickCount, int, aTickLimit, ULocalMultiplayerMenu*, aLocalMultiplayerMenuInstance, int, aSelectedNumberOfPlayers, FAutomationTestBase*, aTest);

#endif //WITH_DEV_AUTOMATION_TESTS