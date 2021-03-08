// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file contains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"
#include "../TestBaseClasses/SimplePIETestBase.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:

DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnARaceBeginningMOCK);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnARaceBeginningCallCountdownStart);





//Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckTimerActive, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRunningStageSpawned, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRaceBeginningStageLoadsAnnouncerUIs, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRaceBeginningStageCountdownToStartModifiesAnnouncerText, FSimplePIETestBase*, test);




#endif //WITH_DEV_AUTOMATION_TESTS