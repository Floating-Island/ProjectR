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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FALapManagerIsntNullWhenInstantiatedTest, 
	"ProjectR.LapManager Tests.Unit.000: Isn't null when instantiated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FALapManagerHasJetsListedWhenSpawnedTest, FSimplePIETestBase,
	"ProjectR.LapManager Tests.Integration.001: Has jets listed when spawned", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FALapManagerJetsHaveFinalLapPhaseAsDefaultPhaseTest, FSimplePIETestBase,
	"ProjectR.LapManager Tests.Integration.002: Jets have the Final lap phase as the default phase", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FALapManagerJetsHaveInitialLapCountSetToOneTest, FSimplePIETestBase,
	"ProjectR.LapManager Tests.Integration.003: Jets have the initial lap count set to one", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FALapManagerJetOverlappingIntermediateChangesPhaseToItFromInitialTest, FSimplePIETestBase,
	"ProjectR.LapManager Tests.Integration.004: Jet that overlaps with intermediate phase changes to it when coming from initial", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FALapManagerJetOverlappingFinalChangesPhaseToItFromIntermediateTest, FSimplePIETestBase,
	"ProjectR.LapManager Tests.Integration.005: Jet that overlaps with final phase changes to it when coming from intermediate", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FALapManagerJetOverlappingInitialChangesPhaseToItFromFinalTest, FSimplePIETestBase,
	"ProjectR.LapManager Tests.Integration.006: Jet that overlaps with initial phase changes to it when coming from final", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FALapManagerJetOverlappingInitialIncreasesLapCountFromFinalTest, FSimplePIETestBase,
	"ProjectR.LapManager Tests.Integration.007: Jet that overlaps with initial from final increases lap count", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)






#endif //WITH_DEV_AUTOMATION_TESTS