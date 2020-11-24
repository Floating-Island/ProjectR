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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARacePreparationStageIsntNullWhenInstantiatedTest, 
	"ProjectR.RacePreparationStage Tests.Unit.000: Isn't null when instantiated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARacePreparationStageNextStageSpawnsRaceBeginningStageTest, 
	"ProjectR.RacePreparationStage Tests.Unit.001: nextStage spawns a race beginning stage", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARacePreparationStagStartSpawnsLapManagerTest, 
	"ProjectR.RacePreparationStage Tests.Unit.002: start spawns a lap manager", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
















#endif //WITH_DEV_AUTOMATION_TESTS