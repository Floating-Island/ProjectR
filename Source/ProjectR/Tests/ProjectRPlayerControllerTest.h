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


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAProjectRPlayerControllerEscKeyLoadsPauseMenuTest,
	"ProjectR.ProjectRPlayerController Tests.Integration.004: Pressing the Esc key brings the pause menu",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAProjectRPlayerControllerEscKeyRemovesPauseMenuIfInViewportTest,
	"ProjectR.ProjectRPlayerController Tests.Integration.005: Pressing the Esc key removes the pause menu if it's already in viewport and hide the mouse cursor",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)



#endif //WITH_DEV_AUTOMATION_TESTS