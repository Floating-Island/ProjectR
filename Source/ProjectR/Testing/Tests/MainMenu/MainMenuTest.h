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
#include "../../TestBaseClasses/SimplePIETestBase.h"

#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUMainMenuIsntNullWhenInstantiatedTest, 
	"ProjectR.MainMenu Tests.Unit.000: Isn't null when instantiated",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FUMainMenuClickingQuitButtonQuitsTheGameTest, FSimplePIETestBase,
	"ProjectR.MainMenu Tests.Unit.001: Clicking the quit button quits the game",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FUMainMenuClickingSingleplayerButtonRemovesMenuFromViewportTest, FSimplePIETestBase,
	"ProjectR.MainMenu Tests.Integration.002: Clicking the singleplayer button removes the menu from viewport",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FUMainMenuClickingSingleplayerButtonBringsSingleplayerMenuTest, FSimplePIETestBase,
	"ProjectR.MainMenu Tests.Integration.003: Clicking the singleplayer button brings the singleplayer menu",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FUMainMenuClickingLocalMultiplayerButtonRemovesMenuFromViewportTest, FSimplePIETestBase,
	"ProjectR.MainMenu Tests.Integration.004: Clicking the local multiplayer button removes the menu from viewport",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FUMainMenuClickingLocalMultiplayerButtonBringsLocalMultiplayerMenuTest, FSimplePIETestBase,
	"ProjectR.MainMenu Tests.Integration.005: Clicking the local multiplayer button brings the localMultiplayer menu",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FUMainMenuClickingLanMultiplayerButtonRemovesMenuFromViewportTest, FSimplePIETestBase,
	"ProjectR.MainMenu Tests.Integration.006: Clicking the lan multiplayer button removes the menu from viewport",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FUMainMenuClickingLanMultiplayerButtonBringsLanMultiplayerMenuTest, FSimplePIETestBase,
	"ProjectR.MainMenu Tests.Integration.007: Clicking the lan multiplayer button brings the lan multiplayer menu",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)




#endif //WITH_DEV_AUTOMATION_TESTS