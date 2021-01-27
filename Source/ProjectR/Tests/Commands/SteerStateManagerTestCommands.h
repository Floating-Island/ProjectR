// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:

DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnASteerStateManagerMOCK);


DEFINE_LATENT_AUTOMATION_COMMAND(FLeftSteerASteerStateManagerMOCK);


DEFINE_LATENT_AUTOMATION_COMMAND(FRightSteerASteerStateManagerMOCK);


DEFINE_LATENT_AUTOMATION_COMMAND(FCenterASteerStateManagerMOCK);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FServerSpawnActorOfClass, UClass*, anActorClass, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FClientSteerLeftSteerStateManager, int, clientQuantity);




//Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckSteerStateManagerCurrentState, UClass*, expectedState, FString, message, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


class USteerState;
DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckSteerStateManagerCurrentStateAgainstPreviousOnSteerLeft, USteerState*, previousState, FString, message, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckSteerStateManagerCurrentStateAgainstPreviousOnSteerRight, USteerState*, previousState, FString, message, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckSteerStateManagerCurrentStateAgainstPreviousOnCenter, USteerState*, previousState, FString, message, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(FCheckSteerStateManagerServerAndClientExpectedState, UClass*, expectedStateClass, int, tickCount, int, tickLimit, int, clientQuantity, FAutomationTestBase*, test);

#endif //WITH_DEV_AUTOMATION_TESTS