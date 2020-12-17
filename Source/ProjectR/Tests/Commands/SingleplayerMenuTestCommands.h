// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"


#if WITH_DEV_AUTOMATION_TESTS


 //Test preparation commands:





 //Test check commands:

class USingleplayerMenu;
DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckSingleplayerMenuClickPlayButtonChangesMap, int, tickCount, int, tickLimit, USingleplayerMenu*, singleplayerMenuInstance, bool, isMenuInstanciated, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckSingleplayerMenuClickGoBackRemovesFromViewport, int, tickCount, int, tickLimit, USingleplayerMenu*, singleplayerMenuInstance, bool, isMenuInstanciated, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckSingleplayerMenuClickGoBackBringsMainMenu, int, tickCount, int, tickLimit, USingleplayerMenu*, singleplayerMenuInstance, bool, isMenuInstanciated, FAutomationTestBase*, test);




#endif //WITH_DEV_AUTOMATION_TESTS
