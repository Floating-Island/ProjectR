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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorIsntNullWhenInstantiatedTest, 
	"ProjectR.TrackGenerator Tests.Unit.000: Isn't null when instantiated", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorHasASplineComponentTest, 
	"ProjectR.TrackGenerator Tests.Unit.001: Has a spline component", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineComponentIsTheRootComponentTest, 
	"ProjectR.TrackGenerator Tests.Unit.002: Spline component is the root component", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorRoadSplinesQuantityIsTheSameAsSplinePointsAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.003: Road splines quantity is the same as spline points at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorRoadSplinesStartPositionsAreTheSameAsSplinePointsAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.004: Road splines start positions are the same as spline points at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorRoadSplinesEndPositionsAreTheSameAsNextSplinePointsAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.005: Road splines end positions are the same as next spline points at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorRoadSplinesStartTangentsAreTheSameAsSplinePointsAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.006: Road splines start tangents are the same as spline points at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorRoadSplinesEndTangentsAreTheSameAsNextSplinePointsAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.007: Road splines end tangents are the same as next spline points at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorRoadSplinesMeshesAreSetAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.008: Road splines meshes are set at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorRoadSplinesMeshesAreTheRoadMeshAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.009: Road splines meshes are the road mesh at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorHasTheSameAmountOfMagnetSplinesAsSplinePointsAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.010: Has the same amount of magnet splines as spline points at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMeshesHaveCollisionEnabledAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.011: Meshes have collision enabled at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMeshesHaveCollisionObjectTypeWorldStaticAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.012: Meshes have collision object type world static at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMeshesAreAttachedToRootAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.013: Meshes are attached to root at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMeshesHaveSameMobilityAsRootAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.014: Meshes have same mobility as root at spawning",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineComponentLoopsTest, 
	"ProjectR.TrackGenerator Tests.Unit.015: Spline component loops", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetSplinesHaveTheSameMobilityAsRoadSplinesAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.016: Magnet splines have the same mobility as road splines at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetSplinesAreAttachedToRoadSplinesAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.017: Magnet splines are attached to road splines at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetSplinesAreOnTopOfRoadSplinesAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.018: Magnet splines are on top of road splines at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetSplinesTangentsAreTheSameAsSplinePointsAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.019: Magnet splines tangents are the same as spline points at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetSplinesMeshesAreSetAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.020: Magnet splines meshes are set at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetSplinesAreHiddenInGameTest, 
	"ProjectR.TrackGenerator Tests.Unit.021: Magnet splines are hidden in game", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetSplinesHaveCollisionEnabledToQueryOnlyTest, 
	"ProjectR.TrackGenerator Tests.Unit.022: Magnet splines have collision enabled to query only", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetSplinesOverlapWithPawnChannelTest, 
	"ProjectR.TrackGenerator Tests.Unit.023: Magnet splines overlap with pawn channel", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorMagnetSplinesGenerateOverlapEventsTest, 
	"ProjectR.TrackGenerator Tests.Unit.024: Magnet splines generate overlap events", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineMeshComponentsHaveSmoothInterpolationEnabledTest, 
	"ProjectR.TrackGenerator Tests.Unit.025: Spline mesh components have smooth interpolation enabled", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorGeneratesOverlapEventsWhenSpawnedTest, 
	"ProjectR.TrackGenerator Tests.Unit.026: Generates overlap events when spawned", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorTrackSectionsQuantityMatchesSplinePointsNumberTest, 
	"ProjectR.TrackGenerator Tests.Unit.027: Track sections quantity is adjusted to the number of spline points", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineMeshComponentsRollAfterSettingRollInEditorTest, 
	"ProjectR.TrackGenerator Tests.Unit.028: Spline mesh components modify their roll when setting it", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSplineMeshComponentsWidenAfterSettingWidenInEditorTest, 
	"ProjectR.TrackGenerator Tests.Unit.029: Spline mesh components modify their width when setting it", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorAllowsDisableCollisionsInEditorTest, 
	"ProjectR.TrackGenerator Tests.Unit.030: Spline mesh components disable collisions when setting it disabled", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorHaveExpectedCollisionsInPIETest, 
	"ProjectR.TrackGenerator Tests.Unit.031: Spline mesh components in PIE have their expected collisions", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorSpawnTrackManagerAtBeginPlayTest, 
	"ProjectR.TrackGenerator Tests.Unit.032: Track generator spawns a track manager at begin play", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorsSpawnOnlyOneTrackManagerAtBeginPlayTest, 
	"ProjectR.TrackGenerator Tests.Unit.033: Track generators spawn only one track manager at begin play", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorBoundsSplinesQuantityIsTheSameAsSplinePointsAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.034: Bound splines quantity is the same as spline points at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorBoundsSplinesAreAttachedToRoadSplinesAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.035: Bounds splines are attached to road splines at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorBoundsSplinesHaveTheSameMobilityAsRoadSplinesAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.037: Bounds splines have the same mobility as road splines at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorBoundsSplinesTangentsAreTheSameAsSplinePointsAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.038: Bounds splines tangents are the same as spline points at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FATrackGeneratorBoundsSplinesMeshesAreSetAtSpawningTest, 
	"ProjectR.TrackGenerator Tests.Unit.039: Bounds splines meshes are set at spawning", 
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)












































#endif //WITH_DEV_AUTOMATION_TESTS