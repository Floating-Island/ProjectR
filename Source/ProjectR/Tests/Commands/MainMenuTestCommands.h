// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"

class UMainMenu;

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:



//Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckMainMenuClickQuits, bool, inPIE, int, aTickCount, int, aTickLimit, UMainMenu*, aMainMenuInstance, FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckMainMenuClickSingleplayerRemovesMenuFromViewport, int, aTickCount, int, aTickLimit, UMainMenu*, aMainMenuInstance, bool, isMenuInstanciated,  FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckMainMenuClickSingleplayerBringsSingleplayerMenu, int, aTickCount, int, aTickLimit, UMainMenu*, aMainMenuInstance, bool, isMenuInstanciated,  FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckMainMenuClickLocalMultiplayerRemovesMenuFromViewport, int, aTickCount, int, aTickLimit, UMainMenu*, aMainMenuInstance, bool, isMenuInstanciated,  FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckSoloMainMenuClickLocalMultiplayerBringsLocalMultiplayerMenu, int, aTickCount, int, aTickLimit, UMainMenu*, aMainMenuInstance, bool, isMenuInstanciated,  FAutomationTestBase*, aTest);


#endif //WITH_DEV_AUTOMATION_TESTS
