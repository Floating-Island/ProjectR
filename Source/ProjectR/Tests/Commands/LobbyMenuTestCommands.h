// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:



//Test check commands:


class FSimplePIETestBase;
class ULobbyMenu;
DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckLobbyMenuClickReturnToMainMenu, ULobbyMenu*, lobbyInstance, bool, menuNeedsInstantiation, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckLobbyMenuClickSelectMapAndStartRace, ULobbyMenu*, lobbyInstance, bool, menuNeedsInstantiation, bool, hasSelectedMap, FSimplePIETestBase*, test);



#endif //WITH_DEV_AUTOMATION_TESTS