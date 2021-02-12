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


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUSessionManagerJoinSessionDoesntStartWithArbitraryDataTest, 
	"ProjectR.SessionManager Tests.Negative.006: joinASession isn't started if fed with arbitrary data", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUSessionManagerIsBoundToFOnCreateSessionCompleteDelegateTest, 
	"ProjectR.SessionManager Tests.Unit.007: is bound to FOnCreateSessionCompleteDelegate", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUSessionManagerIsBoundToFOnStartSessionCompleteDelegateTest, 
	"ProjectR.SessionManager Tests.Unit.008: is bound to FOnStartSessionCompleteDelegate", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUSessionManagerIsBoundToFOnFindSessionsCompleteDelegateTest, 
	"ProjectR.SessionManager Tests.Unit.009: is bound to FOnFindSessionsCompleteDelegate", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUSessionManagerIsBoundToFOnJoinSessionCompleteDelegateTest, 
	"ProjectR.SessionManager Tests.Unit.010: is bound to FOnJoinSessionCompleteDelegate", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUSessionManagerFOnCreateSessionCompleteDelegateHandleIsSetTest, 
	"ProjectR.SessionManager Tests.Unit.011: FOnCreateSessionCompleteDelegate handle is set", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)



	//isBound tests...




#endif //WITH_DEV_AUTOMATION_TESTS