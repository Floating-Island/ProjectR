// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file contains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"
#include "../../TestBaseClasses/SimplePIETestBase.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawningARotatedTrackGeneratorAndJetCloseToIt);





//Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckATrackManagerTrackGenerators, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckATrackManagerStoresJetsWhenOverlap, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckATrackManagerAttractsJets, float, aPreviousDistance, FSimplePIETestBase*, test);




#endif //WITH_DEV_AUTOMATION_TESTS