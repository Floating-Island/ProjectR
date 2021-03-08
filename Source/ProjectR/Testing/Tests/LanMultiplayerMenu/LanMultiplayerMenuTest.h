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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FULanMultiplayerMenuIsntNullWhenInstantiatedTest, 
	"ProjectR.LanMultiplayerMenu Tests.Unit.000: Isn't null when instantiated",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

//buggy. The lan multiplayer menu makes all subsequent UI, replication or session tests to fail...
//Still I don't know what causes this. I need more time to check it out. The weird thing is that it only fails on jenkins. In the session frontend, everything runs as expected.
//IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FULanMultiplayerMenuClickingGoBackButtonRemovesFromViewportTest, FSimplePIETestBase,
//	"ProjectR.LanMultiplayerMenu Tests.Integration.001: Clicking the go back button removes the menu from viewport",
//	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
//
//
//IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FULanMultiplayerMenuClickingGoBackButtonBringsMainMenuTest, FSimplePIETestBase,
//	"ProjectR.LanMultiplayerMenu Tests.Integration.002: Clicking the go back button brings the mainMenu",
//	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
//
//
//IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FULanMultiplayerMenuClickingCreateSessionButtonStartsSessionTest, FSimplePIETestBase,
//	"ProjectR.LanMultiplayerMenu Tests.Integration.003: Clicking the create session travels to the lobby when the session starts",
//	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)



//it automatically searches for sessions and displays them. This isn't tested because it's not possible with only one test instance. Be careful.
//the join button is only clickable if a session is selected.




#endif //WITH_DEV_AUTOMATION_TESTS