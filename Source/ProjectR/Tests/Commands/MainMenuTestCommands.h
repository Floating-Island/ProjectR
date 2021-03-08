// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file contains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"
#include "../TestBaseClasses/SimplePIETestBase.h"

class UMainMenu;

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:



//Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckMainMenuClickQuits, bool, inPIE, UMainMenu*, mainMenuInstance, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckMainMenuClickSingleplayerRemovesMenuFromViewport, UMainMenu*, mainMenuInstance, bool, isMenuInstanciated, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckMainMenuClickSingleplayerBringsSingleplayerMenu, UMainMenu*, mainMenuInstance, bool, isMenuInstanciated, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckMainMenuClickLocalMultiplayerRemovesMenuFromViewport, UMainMenu*, mainMenuInstance, bool, isMenuInstanciated, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckSoloMainMenuClickLocalMultiplayerBringsLocalMultiplayerMenu, UMainMenu*, mainMenuInstance, bool, isMenuInstanciated, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckMainMenuClickLanMultiplayerRemovesMenuFromViewport, UMainMenu*, mainMenuInstance, bool, isMenuInstanciated, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckMainMenuClickLanMultiplayerBringsLanMultiplayerMenu, UMainMenu*, mainMenuInstance, FSimplePIETestBase*, test);


#endif //WITH_DEV_AUTOMATION_TESTS
