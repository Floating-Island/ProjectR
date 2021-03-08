// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file contains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"
#include "../TestBaseClasses/SimplePIETestBase.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FSpawnARacePreparationStage, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnARacePreparationMakeItStart);






//Test check commands:


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckLapManagerSpawned, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckPlayersQuantityOnStart, bool, stageHasStarted, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckPlayersPossessingJets, bool, stageHasStarted, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckJetsInputDisabled, bool, stageHasStarted, FSimplePIETestBase*, test);





#endif //WITH_DEV_AUTOMATION_TESTS