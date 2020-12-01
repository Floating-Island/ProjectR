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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUProjectRGameInstanceIsSetAsProjectGameInstanceTest, 
	"ProjectR.ProjectRGameInstance Tests.Unit.000: Is set as the project's game instance",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUProjectRGameInstanceLoadMainMenuCreatesMainMenuTest, 
	"ProjectR.ProjectRGameInstance Tests.Unit.001: loadMainMenu creates the main menu",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUProjectRGameInstanceLoadMainMenuCreatesOnlyOneMainMenuTest, 
	"ProjectR.ProjectRGameInstance Tests.Unit.001: loadMainMenu creates only one main menu",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUProjectRGameInstanceLoadSoloRaceMenuCreatesSoloRaceMenuTest, 
	"ProjectR.ProjectRGameInstance Tests.Unit.003: loadSoloRaceMenu creates the solo race menu",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUProjectRGameInstanceLoadSoloRaceMenuCreatesOnlyOneSoloRaceMenuTest, 
	"ProjectR.ProjectRGameInstance Tests.Unit.002: loadSoloRaceMenu creates only one solo race menu",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)








#endif //WITH_DEV_AUTOMATION_TESTS