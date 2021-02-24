// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file cointains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"
#include "../TestBaseClasses/SimplePIETestBase.h"

#if WITH_DEV_AUTOMATION_TESTS

class AJet;
 //Test preparation commands:


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FSpawnAJetBehindAnother, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnAJetOnFinalLapMakeItFinish);






//Test check commands:


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRaceGameModeSet, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckRaceGameModeCreatesAllJets, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckRaceGameModeJetsPositioning, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRaceGameModeUpdateStage, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckJetMovedToFinalistJets, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesTheExpectedPlayers, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesTheNecessaryPlayers, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckCreatesSameOrMoreJetsThanPlayers, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FCheckJetsSameRotationAsTrack, int, tickCount, int, tickLimit, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckPlayerStateLapUpdated, AJet*, selectedJet, FSimplePIETestBase*, test);




#endif //WITH_DEV_AUTOMATION_TESTS