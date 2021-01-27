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


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FASteerStateManagerIsntNullWhenInstantiatedTest, 
	"ProjectR.SteerStateManager Tests.Unit.000: Isn't null when instantiated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)
	

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FASteerStateManagerDoesntTickTest, 
	"ProjectR.SteerStateManager Tests.Unit.001: Doesn't tick", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FASteerStateManagerDefaultStateIsCenterTest, 
	"ProjectR.SteerStateManager Tests.Unit.002: The default state is CenterSteerState", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FASteerStateManagerSteerLeftChangesStateToLeftSteerTest, 
	"ProjectR.SteerStateManager Tests.Unit.003: steerLeft changes the current state to LeftSteerState", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FASteerStateManagerSteerRightChangesStateToRightSteerTest, 
	"ProjectR.SteerStateManager Tests.Unit.004: steerRight changes the current state to RightSteerState", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FASteerStateManagerCenterChangesStateToCenterSteerTest, 
	"ProjectR.SteerStateManager Tests.Unit.005: center changes the current state to CenterSteerState", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FASteerStateManagerSteerLeftKeepsStateIfAlreadyLeftSteerStateTest, 
	"ProjectR.SteerStateManager Tests.Unit.006: steerLeft keeps current state if it's already a LeftSteerState", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FASteerStateManagerSteerRightKeepsStateIfAlreadyRightSteerStateTest, 
	"ProjectR.SteerStateManager Tests.Unit.007: steerRight keeps current state if it's already a RightSteerState", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FASteerStateManagerCenterKeepsStateIfAlreadyCenterSteerStateTest, 
	"ProjectR.SteerStateManager Tests.Unit.008: center keeps current state if it's already a CenterSteerState", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FASteerStateManagerReplicatesTest, 
	"ProjectR.SteerStateManager Tests.Replication.009: Replicates to the network", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)








#endif //WITH_DEV_AUTOMATION_TESTS