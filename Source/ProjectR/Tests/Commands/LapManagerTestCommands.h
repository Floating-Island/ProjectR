// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"


//Test preparation commands:

DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerAndJet);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerAInitialLapPhaseAndJet);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerInitalAndIntermediateLapPhasesAndJet);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerIntermediateAndFinalLapPhasesAndJet);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerInitialAndFinalLapPhasesAndJet);



//Test check commands:


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckALapManagerStoresJets, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckJetsInitialLapPhase, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckJetsInitialLapCount, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckJetChangeFromInitialToIntermediate, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckJetChangeFromIntermediateToFinal, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckJetChangeFromFinalToInitial, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(FCheckJetLapCountChangeFromFinalToInitial, int, aTickCount, int, aTickLimit, int, previousLapCount, FAutomationTestBase*, test);






#endif //WITH_DEV_AUTOMATION_TESTS