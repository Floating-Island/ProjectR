// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


/**
 * Each one of this tests should test something of the project class that this test class references to.
 * Each project class should have a test class for it. It's something kind of necessary for TDD.
 * 
 * It's nice if the prettyname follows a pattern like: Game.ClassToTest.Unit.TestName
 * TestName should express what you expect from a test given a scenario.
 * Pay attention to the automation flags because they're needed to run the tests without UI errors.
 */

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceGameModeIsntNullWhenInstantiatedTest, 
	"ProjectR.RaceGameMode Tests.Unit.000: Isn't null when instantiated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceGameModeIsAbleToBeSetInAWorldTest, 
	"ProjectR.RaceGameMode Tests.Unit.001: Is able to be set in a world", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceGameModeCreatesExpectedNumberOfJetsTest, 
	"ProjectR.RaceGameMode Tests.Integration.002: Creates the same amount of jets as expected", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceGameModePositionsJetsBehindTheInitialLapPhaseTest, 
	"ProjectR.RaceGameMode Tests.Integration.003: Positions jets behind the initial lap phase", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceGameModeUpdateStageBringsNextStageTest, 
	"ProjectR.RaceGameMode Tests.Unit.004: updateStage changes the stage to the next stage", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceGameModePositionNumberLowerThanTheOneBehindTest, 
	"ProjectR.RaceGameMode Tests.Integration.005: The position number of a jet is lower than the jet behind", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceGameModeMovesFinalistsJetsTest, 
	"ProjectR.RaceGameMode Tests.Integration.006: Moves a jet to the finalist jets if it completes the final lap", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceGameModePlayersToCreateCreatesThatNumberOfPlayersTest, 
	"ProjectR.RaceGameMode Tests.Integration.007: PlayersToCreate creates that number of players", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceGameModeCreatesTheNecessaryGamePlayersTest, 
	"ProjectR.RaceGameMode Tests.Integration.008: Creates the necessary number of players for the game instance", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


//uses a mock
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceGameModeSameOrMoreNumberOfJetsAsPlayersTest, 
	"ProjectR.RaceGameMode Tests.Integration.008: The number of jets created is the same or more than the number of players", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)



// disable controllers before starting the race and enable them when it starts.
// the quantity of jets to make has to be the same than the number of players (it will be the addition of players plus AI in the future).
// jets should be created taking into account the track section roll.













#endif //WITH_DEV_AUTOMATION_TESTS