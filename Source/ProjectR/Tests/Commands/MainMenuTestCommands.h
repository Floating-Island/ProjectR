// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"
#include "../TestBaseClasses/SimplePIETestBase.h"

class UMainMenu;

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:



//Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckMainMenuClickQuits, bool, inPIE, int, tickCount, int, tickLimit, UMainMenu*, mainMenuInstance, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckMainMenuClickSingleplayerRemovesMenuFromViewport, int, tickCount, int, tickLimit, UMainMenu*, mainMenuInstance, bool, isMenuInstanciated,  FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckMainMenuClickSingleplayerBringsSingleplayerMenu, int, tickCount, int, tickLimit, UMainMenu*, mainMenuInstance, bool, isMenuInstanciated,  FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckMainMenuClickLocalMultiplayerRemovesMenuFromViewport, int, tickCount, int, tickLimit, UMainMenu*, mainMenuInstance, bool, isMenuInstanciated,  FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckSoloMainMenuClickLocalMultiplayerBringsLocalMultiplayerMenu, int, tickCount, int, tickLimit, UMainMenu*, mainMenuInstance, bool, isMenuInstanciated,  FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckMainMenuClickLanMultiplayerRemovesMenuFromViewport, UMainMenu*, mainMenuInstance, bool, isMenuInstanciated,  FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckMainMenuClickLanMultiplayerBringsLanMultiplayerMenu, UMainMenu*, mainMenuInstance, FSimplePIETestBase*, test);


#endif //WITH_DEV_AUTOMATION_TESTS
