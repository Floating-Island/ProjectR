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
DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckSingleplayerMenuClickPlayButtonChangesMap, int, aTickCount, int, aTickLimit, USingleplayerMenu*, aSingleplayerMenuInstance, bool, isMenuInstanciated, FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckSingleplayerMenuClickGoBackRemovesFromViewport, int, aTickCount, int, aTickLimit, USingleplayerMenu*, aSingleplayerMenuInstance, bool, isMenuInstanciated, FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckSingleplayerMenuClickGoBackBringsMainMenu, int, aTickCount, int, aTickLimit, USingleplayerMenu*, aSingleplayerMenuInstance, bool, isMenuInstanciated, FAutomationTestBase*, aTest);




#endif //WITH_DEV_AUTOMATION_TESTS
