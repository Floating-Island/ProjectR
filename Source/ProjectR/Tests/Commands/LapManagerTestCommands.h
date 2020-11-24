// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"


//Test preparation commands:

DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerAndJetCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerAInitialLapPhaseAndJetCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerInitalAndIntermediateLapPhasesAndJetCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerIntermediateAndFinalLapPhasesAndJetCommand);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerInitialAndFinalLapPhasesAndJetCommand);



//Test check commands:


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckALapManagerStoresJetsCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckJetsInitialLapPhaseCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckJetsInitialLapCountCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckJetChangeFromInitialToIntermediateCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckJetChangeFromIntermediateToFinalCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckJetChangeFromFinalToInitialCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckJetLapCountChangeFromFinalToInitialCommand, int, aTickCount, int, aTickLimit, int, previousLapCount, FAutomationTestBase*, test);






#endif //WITH_DEV_AUTOMATION_TESTS