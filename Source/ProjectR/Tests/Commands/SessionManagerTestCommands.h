// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file contains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"
#include "../TestBaseClasses/SimplePIETestBase.h"

#if WITH_DEV_AUTOMATION_TESTS


//Test preparation commands:

DEFINE_LATENT_AUTOMATION_COMMAND(FUSessionManagerCreateSession);



//Test check commands:

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FUSessionManagerCreateAndCheckSessionCreation, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FUSessionManagerCheckTravelToLobby, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FUSessionManagerCheckSessionDestructionStarting, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FUSessionManagerCheckSessionSearching, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSessionManagerSearchResults, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSessionManagerDoesntStartSessionJoin, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSessionManagerBoundToFOnCreateSessionCompleteDelegate, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSessionManagerBoundToFOnStartSessionCompleteDelegate, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSessionManagerBoundToFOnFindSessionsCompleteDelegate, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSessionManagerBoundToFOnJoinSessionCompleteDelegate, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSessionManagerFOnCreateSessionCompleteDelegateHandleSet, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSessionManagerFOnStartSessionCompleteDelegateHandleSet, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSessionManagerFOnFindSessionsCompleteDelegateHandleSet, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSessionManagerFOnJoinSessionCompleteDelegateHandleSet, FAutomationTestBase*, test);


#endif //WITH_DEV_AUTOMATION_TESTS