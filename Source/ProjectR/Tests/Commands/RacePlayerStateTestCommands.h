// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

class ARacePlayerState;
class FSimplePIETestBase;


//Test preparation commands:



//Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckPlayerStateUpdatesRacePlayerUICurrentLap, ARacePlayerState*, raceState, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckPlayerStateUpdatesRacePlayerUICurrentPosition, ARacePlayerState*, raceState, FSimplePIETestBase*, test);

#endif //WITH_DEV_AUTOMATION_TESTS