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
#include "TestBaseClasses/SimplePIETestBase.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FULobbyMenuIsntNullWhenInstantiatedTest, 
	"ProjectR.LobbyMenu Tests.Unit.000: Isn't null when instantiated",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FULobbyMenuClickingReturnGoesToMainMenuTest, FSimplePIETestBase,
	"ProjectR.LobbyMenu Tests.Unit.001: Clicking the return to main menu button loads the main menu map",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FULobbyMenuClickingAMapAndStartRaceChangesWorldTest, FSimplePIETestBase,
	"ProjectR.LobbyMenu Tests.Unit.002: Clicking a map button and then startRaceButton changes the map",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FULobbyMenuIsLoadedInLobbyMapLevelBlueprintTest, FSimplePIETestBase,
	"ProjectR.LobbyMenu Tests.Integration.003: Is loaded by the level blueprint in the lobby map",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)




#endif //WITH_DEV_AUTOMATION_TESTS