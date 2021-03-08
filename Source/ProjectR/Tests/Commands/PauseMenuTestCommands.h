// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file contains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"
#include "../TestBaseClasses/SimplePIETestBase.h"

#if WITH_DEV_AUTOMATION_TESTS


 //Test preparation commands:





 //Test check commands:

class UPauseMenu;
DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckPauseMenuClickReturnButtonChangesToMainMenuMap, UPauseMenu*, pauseMenuInstance, bool, menuIsInstantiated, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckPauseMenuClickResumeButtonRemovesMenuAndResumes, UPauseMenu*, pauseMenuInstance, FSimplePIETestBase*, test);


#endif //WITH_DEV_AUTOMATION_TESTS
