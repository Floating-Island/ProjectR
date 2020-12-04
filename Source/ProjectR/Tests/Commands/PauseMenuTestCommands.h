// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"


#if WITH_DEV_AUTOMATION_TESTS


 //Test preparation commands:





 //Test check commands:

class UPauseMenu;
DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckPauseMenuClickReturnButtonChangesToMainMenuMap, int, aTickCount, int, aTickLimit, UPauseMenu*, aPauseMenuInstance, FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckPauseMenuClickResumeButtonRemovesMenuAndResumes, int, aTickCount, int, aTickLimit, UPauseMenu*, aPauseMenuInstance, FAutomationTestBase*, aTest);


#endif //WITH_DEV_AUTOMATION_TESTS
