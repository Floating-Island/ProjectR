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
	"ProjectR.ProjectRGameInstance Tests.Integration.001: loadMainMenu creates the main menu and adds it to viewport",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUProjectRGameInstanceLoadMainMenuCreatesOnlyOneMainMenuTest, 
	"ProjectR.ProjectRGameInstance Tests.Unit.001: loadMainMenu creates only one main menu",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUProjectRGameInstanceLoadSingleplayerMenuCreatesSingleplayerMenuTest, 
	"ProjectR.ProjectRGameInstance Tests.Integration.003: loadSingleplayerMenu creates the singleplayer menu and adds it to viewport",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUProjectRGameInstanceLoadSingleplayerMenuCreatesOnlyOneSingleplayerMenuTest, 
	"ProjectR.ProjectRGameInstance Tests.Unit.004: loadSingleplayerMenu creates only one singleplayer menu",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUProjectRGameInstanceLoadMainMenuShowsMouseCursorTest, 
	"ProjectR.ProjectRGameInstance Tests.Integration.005: loadMainMenu makes the controller to show the mouse cursor",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUProjectRGameInstanceLoadSingleplayerMenuShowsMouseCursorTest, 
	"ProjectR.ProjectRGameInstance Tests.Integration.006: loadSingleplayerMenu makes the controller to show the mouse cursor",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)






#endif //WITH_DEV_AUTOMATION_TESTS