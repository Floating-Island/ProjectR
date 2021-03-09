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


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceBeginningStageIsntNullWhenInstantiatedTest, 
	"ProjectR.RaceBeginningStage Tests.Unit.000: Isn't null when instantiated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceBeginningStageSubscribesRaceModeToStageEndedEventTest, 
	"ProjectR.RaceBeginningStage Tests.Unit.001: Has its timer active at start", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FARaceBeginningStageNextStageSpawnsRunningStageTest, 
	"ProjectR.RaceBeginningStage Tests.Unit.002: nextStage spawns a race running stage", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FARaceBeginningStageLoadsAnnouncerUIOnStartTest, FSimplePIETestBase,
	"ProjectR.RaceBeginningStage Tests.Integration.003: loads announcerUIs on each controller at start", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST(FARaceBeginningStageCountdownToStartModifiesGameStateAnnouncerTextTest, FSimplePIETestBase,
	"ProjectR.RaceBeginningStage Tests.Integration.004: countdownToStart modifies the gameState's announcer text (except with zero or less)", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)












#endif //WITH_DEV_AUTOMATION_TESTS