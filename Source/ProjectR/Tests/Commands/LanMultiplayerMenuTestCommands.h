// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:



//Test check commands:

class ULanMultiplayerMenu;
DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckLanMultiplayerMenuClickGoBackRemovesFromViewport, ULanMultiplayerMenu*, lanMultiplayerMenuInstance, FAutomationTestBase*, test);


#endif //WITH_DEV_AUTOMATION_TESTS