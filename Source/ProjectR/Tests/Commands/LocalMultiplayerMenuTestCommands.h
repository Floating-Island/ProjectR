// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file contains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"
#include "../TestBaseClasses/SimplePIETestBase.h"

#if WITH_DEV_AUTOMATION_TESTS

class ULocalMultiplayerMenu;

//Test preparation commands:



//Test check commands:


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckLocalMultiplayerMenuClickGoBackRemovesFromViewport, ULocalMultiplayerMenu*, localMultiplayerMenuInstance, bool, isMenuInstanciated, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckLocalMultiplayerMenuClickGoBackBringsMainMenu, ULocalMultiplayerMenu*, localMultiplayerMenuInstance, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckLocalMultiplayerMenuClickPlaySetsPlayers, ULocalMultiplayerMenu*, localMultiplayerMenuInstance, int, aSelectedNumberOfPlayers, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FChecklocalMultiplayerMenuClickPlayButtonChangesMap, ULocalMultiplayerMenu*, localMultiplayerMenuInstance, bool, isMenuInstanciated, FSimplePIETestBase*, test);

#endif //WITH_DEV_AUTOMATION_TESTS