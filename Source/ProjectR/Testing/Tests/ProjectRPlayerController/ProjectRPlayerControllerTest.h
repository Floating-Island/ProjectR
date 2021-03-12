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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAProjectRPlayerControllerIsntNullWhenInstantiatedTest,
	"ProjectR.ProjectRPlayerController Tests.Unit.000: Isn't null when instantiated",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAProjectRPlayerControllerLoadPauseMenuAddsItToViewportTest,
	"ProjectR.ProjectRPlayerController Tests.Integration.001: loadPauseMenu adds the pause menu to viewport",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAProjectRPlayerControllerLoadPauseMenuCreatesOnlyOneInstanceTest,
	"ProjectR.ProjectRPlayerController Tests.Integration.002: loadPauseMenu creates only one instance of pause menu",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAProjectRPlayerControllerLoadPauseMenuShowsMouseCursorTest,
	"ProjectR.ProjectRPlayerController Tests.Integration.003: loadPauseMenu makes the mouse cursor show",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAProjectRPlayerControllerEscKeyLoadsPauseMenuTest, FSimplePIETestBase,
	"ProjectR.ProjectRPlayerController Tests.Integration.004: Pressing the Esc key brings the pause menu",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAProjectRPlayerControllerEscKeyRemovesPauseMenuIfInViewportTest, FSimplePIETestBase,
	"ProjectR.ProjectRPlayerController Tests.Integration.005: Pressing the Esc key removes the pause menu if it's already in viewport and hide the mouse cursor",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAProjectRPlayerControllerLoadPauseMenuPausesTheGameTest,
	"ProjectR.ProjectRPlayerController Tests.Integration.006: loadPauseMenu pauses the game",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAProjectRPlayerControllerLoadPauseMenuUnPausesTheGameIfInViewportTest,
	"ProjectR.ProjectRPlayerController Tests.Integration.007: loadPauseMenu unpauses the game if the pause menu is already in viewport",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAProjectRPlayerControllerFullyTicksWhenGamePausedTest,
	"ProjectR.ProjectRPlayerController Tests.Integration.008: Is set to fully tick when game is paused",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAProjectRPlayerControllerLoadRaceUILoadsthePlayerStateUITest, FSimplePIETestBase,
	"ProjectR.ProjectRPlayerController Tests.Integration.009: loadRaceUI loads the RacePlayerState UI", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAProjectRPlayerControllerLoadRaceUIMakesRacePlayerUISynchronizeVariablesTest, FSimplePIETestBase,
	"ProjectR.ProjectRPlayerController Tests.Integration.010: loadRaceUI makes the loaded RacePlayerUI synchronize its values with the RacePlayerState", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAProjectRPlayerControllerServerRemoveAnnouncerUIRemovesClientLoadedAnnouncerUITest, FSimplePIETestBase,
	"ProjectR.ProjectRPlayerController Tests.Replication.011: Server removeAnnouncerUI removes client loaded announcerUI", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAProjectRPlayerControllerServerLoadResultsUILoadsClientRaceResultsUITest, FSimplePIETestBase,
	"ProjectR.ProjectRPlayerController Tests.Replication.012: Server loadResultsUI loads client RaceResultsUI", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FAProjectRPlayerControllerLoadResultsUIDisablesJetsInputTest, FSimplePIETestBase,
	"ProjectR.ProjectRPlayerController Tests.Unit.013: loadResultsUI disables jets input", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)



#endif //WITH_DEV_AUTOMATION_TESTS