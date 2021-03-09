// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file contains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"
#include "../../TestBaseClasses/SimplePIETestBase.h"

#if WITH_DEV_AUTOMATION_TESTS

class UMotorState;

//Test preparation commands:


DEFINE_LATENT_AUTOMATION_COMMAND(FRetrieveAMotorStateManagerAndAccelerateIt);


DEFINE_LATENT_AUTOMATION_COMMAND(FRetrieveAMotorStateManagerAndBrakeIt);


DEFINE_LATENT_AUTOMATION_COMMAND(FRetrieveAMotorStateManagerAndNeutralizeIt);


DEFINE_LATENT_AUTOMATION_COMMAND(FRetrieveAMotorStateManagerBrakeAccelerateAndNeutralizeIt);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FClientAccelerateMotorStateManager, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FClientBrakeMotorStateManager, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FClientNeutralizeMotorStateManager, int, clientQuantity);


DEFINE_LATENT_AUTOMATION_COMMAND(FRetrieveAMotorStateManagerAndMixIt);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FClientMixMotorStateManager, int, clientQuantity);



//Test check commands:


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMotorStateManagerDefaultState, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMotorStateManagerStateChangesToAccelerating, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMotorStateManagerStateChangesToReversing, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMotorStateManagerStateChangesToNeutral, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckMotorStateManagerAccelerateKeepsStateIfAccelerating, UMotorState*, previousState, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckMotorStateManagerBrakeKeepsStateIfReversing, UMotorState*, previousState, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckMotorStateManagerNeutralizeKeepsStateIfNeutral, UMotorState*, previousState, FSimplePIETestBase*, test);


//DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMotorStateManagerLeavesOneStateInWorld, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckMotorStateManagerServerAndClientExpectedState, UClass*, expectedStateClass, int, clientQuantity, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckMotorStateManagerStateChangesToMixed, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckMotorStateManagerMixKeepsStateIfMixed, UMotorState*, previousState, FSimplePIETestBase*, test);


#endif //WITH_DEV_AUTOMATION_TESTS