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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAFinalLapPhaseIsntNullWhenInstantiatedTest, 
	"ProjectR.FinalLapPhase Tests.Unit.000: Isn't null when instantiated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAFinalLapPhaseUpdateStateReturnsInitialLapPhaseIfItsPassedAsParameterTest, 
	"ProjectR.FinalLapPhase Tests.Unit.001: If a AInitialLapPhase instance is passed to updateState, it returns that instance", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAFinalLapPhaseUpdateStateReturnsItselfIfInitialLapPhaseIsntPassedAsParameterTest, 
	"ProjectR.FinalLapPhase Tests.Unit.002: Returns itself if a AFinalLapPhase instance isn't passed as parameter in updateState", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)



#endif //WITH_DEV_AUTOMATION_TESTS