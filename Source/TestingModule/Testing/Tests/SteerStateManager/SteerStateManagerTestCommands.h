// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file contains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"
#include "../../TestBaseClasses/SimplePIETestBase.h"

#if WITH_DEV_AUTOMATION_TESTS

class USteerState;

//Test preparation commands:


DEFINE_LATENT_AUTOMATION_COMMAND(FLeftSteerASteerStateManagerMOCK);


DEFINE_LATENT_AUTOMATION_COMMAND(FRightSteerASteerStateManagerMOCK);


DEFINE_LATENT_AUTOMATION_COMMAND(FCenterASteerStateManagerMOCK);


//DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FClientSteerLeftSteerStateManager, int, clientQuantity);
//
//
//DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FClientSteerRightSteerStateManager, int, clientQuantity);
//
//
//DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FClientCenterSteerStateManager, int, clientQuantity);




//Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckSteerStateManagerCurrentState, UClass*, expectedState, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckSteerStateManagerCurrentStateAgainstPreviousOnSteerLeft, USteerState*, previousState, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckSteerStateManagerCurrentStateAgainstPreviousOnSteerRight, USteerState*, previousState, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckSteerStateManagerCurrentStateAgainstPreviousOnCenter, USteerState*, previousState, FSimplePIETestBase*, test);


//DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckSteerStateManagerServerAndClientExpectedState, UClass*, expectedStateClass, int, clientQuantity, FSimplePIETestBase*, test);

#endif //WITH_DEV_AUTOMATION_TESTS