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

class USingleplayerMenu;
DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckSingleplayerMenuClickPlayButtonChangesMap, USingleplayerMenu*, singleplayerMenuInstance, bool, isMenuInstanciated, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckSingleplayerMenuClickGoBackRemovesFromViewport, USingleplayerMenu*, singleplayerMenuInstance, bool, isMenuInstanciated, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckSingleplayerMenuClickGoBackBringsMainMenu, USingleplayerMenu*, singleplayerMenuInstance, bool, isMenuInstanciated, FSimplePIETestBase*, test);




#endif //WITH_DEV_AUTOMATION_TESTS
