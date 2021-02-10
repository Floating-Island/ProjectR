// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:

DEFINE_LATENT_AUTOMATION_COMMAND(FUSessionManagerCreateSession);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FClientSpawnSessionManagerAndCreateSession, int32, clientQuantity);


//Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FUSessionManagerCreateAndCheckSessionCreation, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FUSessionManagerCheckTravelToLobby, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FUSessionManagerCheckSessionDestructionStarting, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FUSessionManagerCheckSessionSearching, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


#endif //WITH_DEV_AUTOMATION_TESTS