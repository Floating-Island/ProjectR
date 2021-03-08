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
#include "TestBaseClasses/SimplePIETestBase.h"

#if WITH_DEV_AUTOMATION_TESTS


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceRunningStageIsntNullWhenInstantiatedTest, 
	"ProjectR.RaceRunningStage Tests.Unit.000: Isn't null when instantiated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceRunningStageNextStageSpawnsEndedStageTest, 
	"ProjectR.RaceRunningStage Tests.Integration.001: nextStage spawns a race ended stage", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceRunningStageSpawnsEndedStageWhenNoRunningJetsTest, 
	"ProjectR.RaceRunningStage Tests.Integration.002: Spawns race ended stage if no running jets", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FARaceRunningStageEnablesJetsInputOnStartTest, FSimplePIETestBase,
	"ProjectR.RaceRunningStage Tests.Integration.003: Enables jets input on start", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FARaceRunningStageStartInitiatesRemovalOfAnnouncerUIsTest, FSimplePIETestBase,
	"ProjectR.RaceRunningStage Tests.Integration.004: start starts the removal of loaded AnnouncerUIs", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
















#endif //WITH_DEV_AUTOMATION_TESTS