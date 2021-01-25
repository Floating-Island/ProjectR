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




IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAMotorStateManagerIsntNullWhenInstantiatedTest, 
	"ProjectR.MotorStateManager Tests.Unit.000: Isn't null when instantiated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAMotorStateManagerDefaultStateIsNeutralTest, 
	"ProjectR.MotorStateManager Tests.Unit.001: The default state is NeutralMotorState", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAMotorStateManagerAccelerateChangesStateToAcceleratingTest, 
	"ProjectR.MotorStateManager Tests.Unit.002: accelerate changes the motor state to Accelerating", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAMotorStateManagerBrakeChangesStateToReversingTest, 
	"ProjectR.MotorStateManager Tests.Unit.003: brake changes the motor state to Reversing", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAMotorStateManagerNeutralizeChangesStateToNeutralTest, 
	"ProjectR.MotorStateManager Tests.Unit.004: neutralize changes the motor state to Neutral", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAMotorStateManagerAccelerateKeepsStateIfAlreadyAcceleratingTest, 
	"ProjectR.MotorStateManager Tests.Unit.005: accelerate keeps the state if it's already Accelerating", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAMotorStateManagerBrakeKeepsStateIfAlreadyReversingingTest, 
	"ProjectR.MotorStateManager Tests.Unit.006: brake keeps the state if it's already Reversing", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAMotorStateManagerNeutralizeKeepsStateIfAlreadyNeutralTest, 
	"ProjectR.MotorStateManager Tests.Unit.007: neutralize keeps the state if it's already Neutral", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

//this test is commented because after making the motor state a UObject I have to rely solely on the garbage collector.
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAMotorStateManagerNeutralizeAccelerateAndBrakeOnlyLeaveOneStateInMemoryTest, 
//	"ProjectR.MotorStateManager Tests.Unit.008: neutralize, accelerate and/or brake keep only one state in memory", 
//	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAMotorStateManagerReplicatesTest, 
	"ProjectR.MotorStateManager Tests.Replication.009: Replicates", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAMotorStateManagerAlwaysRelevantTest, 
	"ProjectR.MotorStateManager Tests.Replication.010: Is always relevant for network", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAMotorStateManagerReplicatesStateWhenCallingAccelerateTest, 
	"ProjectR.MotorStateManager Tests.Replication.011: Replicates state when calling accelerate", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAMotorStateManagerReplicatesStateWhenCallingBrakeTest, 
	"ProjectR.MotorStateManager Tests.Replication.012: Replicates state when calling brake", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAMotorStateManagerReplicatesStateWhenCallingNeutralizeTest, 
	"ProjectR.MotorStateManager Tests.Replication.013: Replicates state when calling neutralize", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAMotorStateManagerMixChangesStateToMixedTest, 
	"ProjectR.MotorStateManager Tests.Unit.014: mix changes the motor state to Mixed", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
	

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAMotorStateManagerMixKeepsStateIfAlreadyMixedTest, 
	"ProjectR.MotorStateManager Tests.Unit.015: mix keeps the state if it's already Mixed", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)





#endif //WITH_DEV_AUTOMATION_TESTS