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
DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckLocalMultiplayerMenuClickGoBackRemovesFromViewport, int, tickCount, int, tickLimit, ULocalMultiplayerMenu*, localMultiplayerMenuInstance, bool, isMenuInstanciated, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckLocalMultiplayerMenuClickGoBackBringsMainMenu, int, tickCount, int, tickLimit, ULocalMultiplayerMenu*, localMultiplayerMenuInstance, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckLocalMultiplayerMenuClickPlaySetsPlayers, int, tickCount, int, tickLimit, ULocalMultiplayerMenu*, localMultiplayerMenuInstance, int, aSelectedNumberOfPlayers, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FChecklocalMultiplayerMenuClickPlayButtonChangesMap, int, tickCount, int, tickLimit, ULocalMultiplayerMenu*, localMultiplayerMenuInstance, bool, isMenuInstanciated, FAutomationTestBase*, test);

#endif //WITH_DEV_AUTOMATION_TESTS