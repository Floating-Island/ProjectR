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


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAAcceleratingMotorStateIsntNullWhenInstantiatedTest, 
	"ProjectR.AcceleratingMotorState Tests.Unit.000: Isn't null when instantiated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAAcceleratingMotorStateIsAcceleratingTest, 
	"ProjectR.AcceleratingMotorState Tests.Unit.001: isAccelerating returns true", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAAcceleratingMotorStateIsntReversingTest, 
	"ProjectR.AcceleratingMotorState Tests.Unit.002: isReversing returns false", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAAcceleratingMotorStateActivateAcceleratesMotorDriveTest, 
	"ProjectR.AcceleratingMotorState Tests.Integration.003: activate accelerates the motor drive component passed as parameter ", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)





#endif //WITH_DEV_AUTOMATION_TESTS