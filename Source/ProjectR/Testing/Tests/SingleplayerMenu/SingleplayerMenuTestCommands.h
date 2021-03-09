// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file contains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"
#include "../../TestBaseClasses/SimplePIETestBase.h"


#if WITH_DEV_AUTOMATION_TESTS

class USingleplayerMenu;

 //Test preparation commands:





 //Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckSingleplayerMenuClickMapAndPlayButtonChangesMap, USingleplayerMenu*, singleplayerMenuInstance, bool, menuNeedsInstantiation, bool, hasSelectedMap, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckSingleplayerMenuClickGoBackRemovesFromViewport, USingleplayerMenu*, singleplayerMenuInstance, bool, isMenuInstanciated, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckSingleplayerMenuClickGoBackBringsMainMenu, USingleplayerMenu*, singleplayerMenuInstance, bool, isMenuInstanciated, FSimplePIETestBase*, test);




#endif //WITH_DEV_AUTOMATION_TESTS
