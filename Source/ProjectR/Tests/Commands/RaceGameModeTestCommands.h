// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS


 //Test preparation commands:


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FSpawnAJetBehindAnotherCommand, FAutomationTestBase*, test);






//Test check commands:


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRaceGameModeSetCommand, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckRaceGameModeCreatesAllJetsCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckRaceGameModeJetsPositioningCommand, int, aTickCount, int, aTickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRaceGameModeUpdateStageCommand, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckJetMovedToFinalistJets, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesTheExpectedPlayers, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesTheNecessaryPlayers, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckCreatesSameOrMoreJetsThanPlayers, int, aTickCount, int, aTickLimit, FAutomationTestBase*, aTest);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckJetsSameRotationAsTrack, int, aTickCount, int, aTickLimit, FAutomationTestBase*, aTest);




#endif //WITH_DEV_AUTOMATION_TESTS