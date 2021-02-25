// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"
#include "../TestBaseClasses/SimplePIETestBase.h"


#if WITH_DEV_AUTOMATION_TESTS

class AProjectRPlayerControllerMOCK;
class AProjectRPlayerController;

 //Test preparation commands:





 //Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckPlayerControllerBringsPauseMenu, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckPlayerControllerCreatesUniquePauseMenuInstance, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckPlayerControllerShowsMouseCursor, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckPlayerControllerPressEscBringsPauseMenu, AProjectRPlayerControllerMOCK*, testPlayerController, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckPlayerControllerPressEscRemovesPauseMenuInViewport, AProjectRPlayerControllerMOCK*, testPlayerController, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckPlayerControllerLoadPauseMenuPausesTheGame, AProjectRPlayerControllerMOCK*, testPlayerController, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckPlayerControllerLoadPauseMenuUnPausesTheGameIfInViewport, AProjectRPlayerControllerMOCK*, testPlayerController, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckPRPlayerControllerLoadsPlayerStateUI, AProjectRPlayerController*, testPlayerController, FSimplePIETestBase*, test);



#endif //WITH_DEV_AUTOMATION_TESTS
