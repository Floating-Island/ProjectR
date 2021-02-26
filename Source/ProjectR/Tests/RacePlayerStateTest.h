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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARacePlayerStateIsntNullWhenInstantiatedTest, 
	"ProjectR.RacePlayerState Tests.Unit.000: Isn't null when instantiated",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FARacePlayerStateUpdateLapToUpdatesSubscribedRacePlayerUICurrentLapTest, FSimplePIETestBase,
	"ProjectR.RacePlayerState Tests.Integration.001: updateLapTo updates subscribed RacePlayerUIs currentLap", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FARacePlayerStateUpdatePositionToUpdatesSubscribedRacePlayerUICurrentPositionTest, FSimplePIETestBase,
	"ProjectR.RacePlayerState Tests.Integration.002: updatePositionTo updates subscribed RacePlayerUIs currentPosition", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FARacePlayerStateLoadRaceUIMakesRacePlayerUISynchronizeVariablesTest, FSimplePIETestBase,
	"ProjectR.RacePlayerState Tests.Integration.003: loadRaceUI makes the loaded RacePlayerUI synchronize its values", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
	


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FARacePlayerStateServerUpdateLapToUpdatesSubscribedClientRacePlayerUICurrentLapTest, FSimplePIETestBase,
	"ProjectR.RacePlayerState Tests.Replication.004: Server updateLapTo updates subscribed client RacePlayerUIs currentLap", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)






#endif //WITH_DEV_AUTOMATION_TESTS