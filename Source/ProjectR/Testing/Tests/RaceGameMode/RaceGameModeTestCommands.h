// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * This file contains the latent commands necessary for the tests.
 */

#include "Misc/AutomationTest.h"
#include "../../TestBaseClasses/SimplePIETestBase.h"

#if WITH_DEV_AUTOMATION_TESTS

class AJet;
 //Test preparation commands:


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FSpawnAJetBehindAnother, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnAJetOnFinalLapMakeItFinish);


DEFINE_LATENT_AUTOMATION_COMMAND(FSpawnAControlledJetOnFinalLapMakeItFinish);






//Test check commands:


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRaceGameModeSet, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRaceGameModeCreatesAllJets, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRaceGameModeJetsPositioning, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckRaceGameModeUpdateStage, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckJetMovedToFinalistJets, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesTheExpectedPlayers, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesTheNecessaryPlayers, FAutomationTestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckCreatesSameOrMoreJetsThanPlayers, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckJetsSameRotationAsTrack, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckPlayerStateLapUpdated, AJet*, selectedJet, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckPlayerStatePositionUpdated, AJet*, selectedJet, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckPlayerStateTotalLapsUpdated, AJet*, selectedJet, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckSameRaceUIQuantityAsControllers, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(FCheckServerRaceGameModePreventsPausing, int, clientQuantity, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckGameModeRaceResultsLoaded, FSimplePIETestBase*, test);


DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FCheckGameModeDisablesInput, FSimplePIETestBase*, test);




#endif //WITH_DEV_AUTOMATION_TESTS