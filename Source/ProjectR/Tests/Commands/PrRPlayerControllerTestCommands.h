// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"


#if WITH_DEV_AUTOMATION_TESTS


 //Test preparation commands:





 //Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckPlayerControllerBringsPauseMenu, FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckPlayerControllerCreatesUniquePauseMenuInstance, FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckPlayerControllerShowsMouseCursor, FAutomationTestBase*, aTest);



#endif //WITH_DEV_AUTOMATION_TESTS
