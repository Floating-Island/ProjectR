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


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseIsntNullWhenInstantiatedTest, 
	"ProjectR.LapPhase Tests.Unit.000: Isn't null when instantiated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseHasAStaticMeshComponentTest, 
	"ProjectR.LapPhase Tests.Unit.001: Has a static mesh component", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseHasAStaticMeshTest, 
	"ProjectR.LapPhase Tests.Unit.002: Has a static mesh associated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseHasPhaseWallAsRootTest, 
	"ProjectR.LapPhase Tests.Unit.003: The phase wall is the root component", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseHasCollisionEnabledToQueryOnlyTest, 
	"ProjectR.LapPhase Tests.Unit.004: Has collision enabled to query only at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseOverlapsWithPawnChannelTest, 
	"ProjectR.LapPhase Tests.Unit.005: Overlaps with the pawn channel", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseObjectTypeIsWorldStaticTest, 
	"ProjectR.LapPhase Tests.Unit.006: Its object type is world static", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseGeneratesOverlapEventsTest, 
	"ProjectR.LapPhase Tests.Unit.007: Generates overlap events", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseUpdateStateReturnsItselfTest, 
	"ProjectR.LapPhase Tests.Unit.008: updateState returns itself", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseIsHiddenInGameTest, 
	"ProjectR.LapPhase Tests.Unit.009: Is hidden in game", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapPhaseDefaultAllowedDistanceIsMaximumPossibleTest, 
	"ProjectR.LapPhase Tests.Unit.010: Default allowed distance is the maximum possible", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)













#endif //WITH_DEV_AUTOMATION_TESTS