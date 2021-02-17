// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"
#include "../TestBaseClasses/SimplePIETestBase.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:



//Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckAStringScrollBoxPopulateBoxNumberOfChilds, FSimplePIETestBase*, test);


class UStringHolderButton;
DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckAStringScrollBoxChildClicked, UStringHolderButton*, aButtonHolder, FSimplePIETestBase*, test);



#endif //WITH_DEV_AUTOMATION_TESTS