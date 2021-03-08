// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file contains the latent commands necessary for the tests.
 */

#if WITH_DEV_AUTOMATION_TESTS

#include "Misc/AutomationTest.h"
#include "../../TestBaseClasses/SimplePIETestBase.h"


//Test preparation commands:

DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerAndJet);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerAInitialLapPhaseAndJet);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerInitalAndIntermediateLapPhasesAndJet);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerIntermediateAndFinalLapPhasesAndJet);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningALapManagerInitialAndFinalLapPhasesAndJet);



//Test check commands:


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckALapManagerStoresJets, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckJetsInitialLapPhase, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckJetsInitialLapCount, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckJetChangeFromInitialToIntermediate, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckJetChangeFromIntermediateToFinal, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckJetChangeFromFinalToInitial, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckJetLapCountChangeFromFinalToInitial, int, previousLapCount, FSimplePIETestBase*, test);






#endif //WITH_DEV_AUTOMATION_TESTS