// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"
#include "../TestBaseClasses/SimplePIETestBase.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:



//Test check commands:


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckLobbyGameStateExistsInLobby, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckLobbyGameStateUpdatesClientLobbyMenus, FString, selectedMap, bool, needsToSelectMap, int, clientQuantity, FSimplePIETestBase*, test);


#endif //WITH_DEV_AUTOMATION_TESTS