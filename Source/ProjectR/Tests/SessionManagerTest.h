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


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUSessionManagerIsntNullWhenInstantiatedTest, 
	"ProjectR.SessionManager Tests.Unit.000: Isn't null when instantiated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUSessionManagerCreateLANSessionStartsTheCreationOfSessionTest, 
	"ProjectR.SessionManager Tests.Unit.001: createLANSession starts the creation of a LAN session", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUSessionManagerCreateLANSessionTravelsToLobbyWhenStartedTest, 
	"ProjectR.SessionManager Tests.Unit.002: createLANSession travels to lobby when it starts", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUSessionManagerDestroyCurrentSessionStartsSessionDestructionTest, 
	"ProjectR.SessionManager Tests.Unit.003: destroyCurrentSession starts session destruction", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUSessionManagerSearchLANSessionsStartsTheSearchOfSessionsTest, 
	"ProjectR.SessionManager Tests.Unit.004: searchLANSessions starts the search of LAN sessions", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUSessionManagerSessionSearchResultsReturnsIDsFromSearchResultsTest, 
	"ProjectR.SessionManager Tests.Unit.005: sessionSearchResults returns IDs of sessions from SearchResults", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUSessionManagerJoinSessionStartsWithArbitraryDataTest, 
	"ProjectR.SessionManager Tests.Unit.006: joinASession is started if fed with arbitrary data", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)








#endif //WITH_DEV_AUTOMATION_TESTS