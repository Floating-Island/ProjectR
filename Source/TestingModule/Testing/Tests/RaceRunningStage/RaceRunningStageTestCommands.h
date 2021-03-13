// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file contains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"
#include "../../TestBaseClasses/SimplePIETestBase.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnARaceRunningCallNextStage);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnARaceRunningAndStart);




//Test check commands:


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckEndedStageSpawned, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckEndedStageSpawnedWithNoRunningJets, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckARaceRunningStartEnablesJetsInput, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckRaceRunningStartsAnnouncerUIsRemoval, bool, controllersNeedAnnouncerLoad, FSimplePIETestBase*, test);




#endif //WITH_DEV_AUTOMATION_TESTS